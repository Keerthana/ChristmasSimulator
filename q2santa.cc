#include "q2santa.h"

_Cormonitor Printer;

void Santa::main() {
  yield(mprng(10));
  // Santa is starting (S)
  prt_->print(id_, Printer::Starting);
  for (;;) {
    yield(mprng(3));
    // Santa about to try and nap (N)
    prt_->print(id_, Printer::Napping);
    status = wrk_->sleep();
    prt_->print(id_, Printer::Awake);

    switch (status) {
    case Workshop::Consulting:
      prt_->print(id_, Printer::Consulting);
      yield(mprng(3));
      wrk_->doneConsulting(id_);
      prt_->print(id_, Printer::DoneConsulting);
      continue;
    case Workshop::Delivery:
      prt_->print(id_, Printer::DeliveringToys);
      yield(mprng(5));
      wrk_->doneDelivering(id_);
      prt_->print(id_, Printer::DoneDelivering);
      continue;
    case Workshop::Done:
      break;
    default:
      break;
    }
    break;
  }
  // Santa is terminating (F)
  prt_->print(id_, Printer::Finished);
}

Santa::Santa(Workshop &wrk, Printer &prt) : wrk_(&wrk), prt_(&prt), id_(0) {}
