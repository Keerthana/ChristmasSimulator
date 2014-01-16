#ifndef Q2REINDEER_H
#define Q2REINDEER_H
#include "q2workshop.h"

_Task Reindeer {
  void main();

public:
  enum {
    MAX_NUM_REINDEER = 5
  }; // number of reindeer in system for delivering toys
  Reindeer(unsigned int id, Workshop & wrk, Printer & prt,
           unsigned int numDeliveries);

private:
  unsigned int id_;
  Workshop *wrk_;
  Printer *prt_;
  unsigned int numDeliveries_;
}
;
#endif // Q2REINDEER_H
