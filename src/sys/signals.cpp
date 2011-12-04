/* @file signals.cpp
 *
 * @note based on LLVM Signals code
 */
#include "sys/signals.h"
#include "arch/linux_common.h"
#include <execinfo.h>  /* backtrace */
#include <signal.h>    /* sigfillset */
#include <dlfcn.h>
#include <cxxabi.h>

using namespace mdw;


/* function to be called when CTRL-C is pressed */
static void (*interrupt_function)() = 0;

/* signals that may interrupt the program at any time */
static const int interrupt_signals[] = {
  SIGHUP, 
  SIGINT, 
  SIGQUIT, 
  SIGPIPE, 
  SIGTERM, 
  SIGUSR1, 
  SIGUSR2
};
static const int sz_interrupt_signals = 
  sizeof(interrupt_signals)/sizeof(interrupt_signals[0]);
static const int *interrupt_signals_end = interrupt_signals + sz_interrupt_signals;

/* signals that are synchronous with the program which will cause it to die */
static const int kill_signals[] = {
  SIGILL, 
  SIGTRAP, 
  SIGABRT, 
  SIGFPE, 
  SIGBUS, 
  SIGSEGV
};
static const int sz_kill_signals = sizeof(kill_signals)/sizeof(kill_signals[0]);
static const int *kill_signals_end = kill_signals + sz_kill_signals;

static int n_registered_signals = 0;
static struct {
  struct sigaction sigact;
  int signo;
} registered_signals[sz_interrupt_signals + sz_kill_signals];
static const int sz_registered_signals = 
  sizeof(registered_signals)/sizeof(registered_signals[0]); 


static void register_handler(int sig) 
{
  assert(n_registered_signals < sz_registered_signals &&
	 "out of space for signal handlers!");
  struct sigaction handler;
  handler.sa_handler = signal_handler;
  handler.sa_flags = SA_NODEFER | SA_RESETHAND;
  sigemptyset(&handler.sa_mask);
  
  /* install the new handler, save the old one in registered_signals */
  sigaction(sig, &handler, &registered_signals[n_registered_signals].sigact);

  n_registered_signals++;
}

static void register_handlers()
{
  if (n_registered_signals != 0) return;

  std::for_each(interrupt_signals, interrupt_signals_end, register_handler);
  std::for_each(kill_signals, kill_signals_end, register_handler);
}

static void unregister_handlers()
{
  for (int i = 0; i < n_registered_signals; i++)
    sigaction(registered_signals[i].signo, &registered_signals[i].sigact, 0);
  n_registered_signals = 0;
}

static void signal_handler(int sig)
{
  /* restored the signal behavior to default, so the program actually crashes
     when we return and the signal reissues; this also ensures that if we
     crash in our signal handler that the program will terminate immediately
     instead of recursing in the signal handler */
  unregister_handlers();

  /* unmask all potentially blocked kill signals */
  sigset_t sigmask;
  sigfillset(&sigmask);
  sigprocmask(SIG_UNBLOCK, &sigmask, 0);

  signals_mtx.acquire();
  
  /* if the signal is an interrupt signal */
  if (std::find(interrupt_signals, interrupt_signals_end, sig) != 
      interrupt_signals_end) {

    if (interrupt_function) {
      /* run the interrupt function */
      void (*int_func)() = interrupt_function;
      signals_mtx.release();
      interrupt_function = 0;
      int_func();
      return;
    }

    /* execute the default handler */
    signals_mtx.release();
    raise(sig);
    return;
  }

  signal_mtx.release();
  
  /* if the signal is not an interrupt signal */
  for (i = 0; i < n_callbacks_to_run; i++) 
    callbacks_to_run[i].first(callbacks_to_run[i].second);
}


/* prints the stack trace */
static void print_stack_trace(void *)
{
  static void *stack[256];
  in depth = backtrace(stack, static_cast<int>(array_lengthof(stack)));
}

