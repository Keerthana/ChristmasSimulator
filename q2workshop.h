/* */
#ifndef Q2WORKSHOP_H
#define Q2WORKSHOP_H

#include "q2printer.h"

_Monitor Workshop {
  // private members go here
public:
  enum Status {
    Consulting,
    Delivery,
    Done
  };
  // printer, bound, elves, reindeer delivery
  Workshop(Printer & prt, unsigned int N, unsigned int E, unsigned int D);

  // santa calls to nap; when Santa wakes status of next action
  Status sleep();

  // reindeer call to deliver toys
  void deliver(unsigned int id);

  // elves call to consult Santa,
  //   true => consultation successful, false => consultation failed
  bool consult(unsigned int id);

  // block Santa/elves until meeting over
  void doneConsulting(unsigned int id);

  // block Santa/reindeer until all toys are delivered
  void doneDelivering(unsigned int id);

  // elves call to indicate termination
  void termination(unsigned int id);

private:
  Printer *prt_;
  // Application setting variables
  unsigned int N_, E_, D_, C, R;
  // Counters
  unsigned int n, e, r;
  unsigned int blockedElf, blockedReindeer;

  uCondition santa, elves, reindeers;
  uCondition consultation, delivery;
}
;
#endif // Q2WORKSHOP_H
