/* @file event.h
 *
 * Event is one of the core Meadow classes. The runtime is basically responsible
 * for scheduling the wakeup of event consumers when event is produced. An
 * event consumer can generate a new set of events which in turn are used
 * for scheduling further wakeups.
 */
#ifndef MDW_WORKFLOW_EVENT_H
#define MDW_WORKFLOW_EVENT_H

namespace mdw {

namespace workflow {


class EventType {
  
};

/*  */
class Event {

  /* types of events to be used to identify subclasses */
  enum EventE {
    
  };

  /* status of events */
  enum EventStatus {
    EVENT_PENDING,     /* right after event was generated */
    EVENT_DELIVERED,   /* event was delivered to all its consumers */
    EVENT_SERVED       /* event has finished its life cycle */
  };


  void addProducer(EventProducer& ep);
  void getNumProducers() const;

  void addConsumer(EventConsumer& ec);
  void getNumConsumers() const;


  void dump() const;
  void print(ostream& os) const;
};


class EventProducer {

};

class EventConsumer {
};


} /* workflow */
} /* mdw */

#endif /* MDW_WORKFLOW_EVENT_H */
