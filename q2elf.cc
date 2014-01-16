#include "q2elf.h"

void Elf::main() {
  yield(mprng(10));

  // Elf is starting (S)
  prt_->print(id_, Printer::Starting);

  for (unsigned int i = 0; i < numConsultations_; ++i) {
    yield(mprng(3));

    // Elf is working (W)
    prt_->print(id_, Printer::Working);
    yield(mprng(5));

    // Elf needs Santa's help (H)
    prt_->print(id_, Printer::NeedHelp);
    isConsulting = wrk_->consult(id_);
    if (isConsulting) {

      // Elf is consulting with Santa (C)
      prt_->print(id_, Printer::Consulting);
      yield(mprng(3));

      // Elf is done consulting with Santa (c)
      prt_->print(id_, Printer::DoneConsulting);
      wrk_->doneConsulting(id_);
    } else {

      // Elf failed to consult with Santa (X)
      prt_->print(id_, Printer::ConsultingFailed);
      break;
    }
  }

  // Elf is terminating (F)
  prt_->print(id_, Printer::Finished);
  wrk_->termination(id_);
}
Elf::Elf(unsigned int id, Workshop &wrk, Printer &prt,
         unsigned int numConsultations)
    : id_(id + 1), wrk_(&wrk), prt_(&prt), numConsultations_(numConsultations) {}