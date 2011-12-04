/* @file mutex.h
 *
 * 
 */
#ifndef MDW_SYS_MUTEX_H
#define MDW_SYS_MUTEX_H

namespace mdw {
namespace sys {

  class Mutex {
  
  public:
    /* attempts to unconditionally acquire the lock; if the lock is 
       held by another thread, this will wait until it can acquire the lock;
       @ returns 0 if any error occurs, 1 otherwise */ 
    int acquire();

    /* attempts to release the lock; if the lock is held by the current 
       thread, the lock is released allowing other threads to acquire the
       lock;
       @ returns 0 if any error occurs, 1 otherwise */
    int release();
  };
  
    
} /* sys */
} /* mdw */

#endif /* MDW_SYS_MUTEX_H */
