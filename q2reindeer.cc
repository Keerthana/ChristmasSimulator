#include "q2reindeer.h"

void Reindeer::main() {
  yield(mprng(10));
 
  // Reindeer is starting (S)
  prt_->print(id_, Printer::Starting);

  for (unsigned int i = 0; i < numDeliveries_; ++i) {
    yield(mprng(3));

    // Reindeer is on a vacation (V)
    prt_->print(id_, Printer::OnVacation);
    yield(mprng(5));
 
    // Reindeer is checking-in (I)
    prt_->print(id_, Printer::CheckingIn);
    wrk_->deliver(id_);

    // Santa/ Reindeer are delivering toys (D)
    prt_->print(id_, Printer::DeliveringToys);
    yield(mprng(5));

    // Santa/ Reindeer are done delivering toys (d)
    prt_->print(id_, Printer::DoneDelivering);
    wrk_->doneDelivering(id_);
  }
 
  // Reindeer is terminating (F)
  prt_->print(id_, Printer::Finished);
}
Reindeer::Reindeer(unsigned int id, Workshop &wrk, Printer &prt,
                   unsigned int numDeliveries)
    : id_(id + 1), wrk_(&wrk), prt_(&prt), numDeliveries_(numDeliveries) {}
