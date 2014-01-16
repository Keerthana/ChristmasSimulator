#include "q2workshop.h"
#include "q2elf.h"
#include "q2reindeer.h"

Workshop::Workshop(Printer &printer, unsigned int N, unsigned int E,
                   unsigned int D)
    : prt_(&printer), N_(N),         // Bound on service offered to Reindeers
      E_(E),                         // Number of Elves
      D_(D),                         // Number of deliveries to be made
      C(Elf::CONSULTING_GROUP_SIZE), // Number of Elves needed to wake Santa up
      R(Reindeer::MAX_NUM_REINDEER), // Number of Reindeers
      n(0),                          // Counter for Elves between 0 and consulting size
      e(0),                          // Counter for Elves between 0 and N
      r(0),                          // Counter for Reindeers between 0 and R
      blockedElf(0),                 // number of blocked Elves
      blockedReindeer(0)             // number of blocked Reindeers
{}

// santa calls to nap; when Santa wakes status of next action
Workshop::Status Workshop::sleep() {

  // Santa is Either consulting with Elves, or delivering with Reindeers
  if (r >= R && !(n >= N_ && e >= C)) {
    if (e >= C)
      n++;
    for (unsigned int i = 0; i < R; ++i)
      reindeers.signal();
    r -= R;
    return Delivery;
  } else if (e >= C) {
    n = 0;
    for (unsigned int i = 0; i < C; ++i)
      elves.signal();
    e -= C;
    return Consulting;
  } else if (D_ == 0 && E_ == 0)
    return Done;

  // Santa goes to Sleep when Elf / Reindeers are not present
  prt_->print(0, Printer::Blocked);
  santa.wait();

  // Santa is Either consulting with Elves, or delivering with Reindeers
  if (r >= R && !(n >= N_ && e >= C)) {
    if (e >= C)
      n++;
    for (unsigned int i = 0; i < R; ++i)
      reindeers.signal();
    r -= R;
    return Delivery;
  } else if (e >= C) {
    n = 0;
    for (unsigned int i = 0; i < C; ++i)
      elves.signal();
    e -= C;
    return Consulting;
  }

  return Done;
}

void Workshop::deliver(unsigned int id) {
  r++;
  if (r >= R) santa.signal();

  // Reindeer r is blocked by Santa (B)
  prt_->print(id, Printer::Blocked, r);
  reindeers.wait();
  
  // Reindeer r is unblocked by Reindeer id (U)
  prt_->print(id, Printer::Unblocked, r);
}

bool Workshop::consult(unsigned int id) {
  if (E_ < C) return false;
  e++;
  if (e >= C) santa.signal();

  // Elf e is blocked by Santa (B)
  prt_->print(id, Printer::Blocked, e);
  elves.wait();

  // Elf e is unblocked by Elf id (U)
  prt_->print(id, Printer::Unblocked, e);

  if (E_ < C) return false;
  return true;
}

void Workshop::doneConsulting(unsigned int id) {
  blockedElf++;
  if (blockedElf <= C) {

    // Consultation is blocked by already consulting Elf id (B)
    prt_->print(id, Printer::Blocked, blockedElf);
    consultation.wait();

    // Consultation is unblocked by already consulting Elf id (B)
    prt_->print(id, Printer::Unblocked, blockedElf);
  } else {
    for (unsigned int i = 0; i < C; ++i)
      consultation.signal();
  }
  blockedElf--;
}

void Workshop::doneDelivering(unsigned int id) {
  blockedReindeer++;
  if (blockedReindeer <= R) {

    // Delivery is blocked by already consulting Reindeer id (B)
    prt_->print(id, Printer::Blocked, blockedReindeer);
    delivery.wait();

    // Delivery is unblocked by already consulting Reindeer id (B)
    prt_->print(id, Printer::Unblocked, blockedReindeer);
  } else {
    for (unsigned int i = 0; i < R; ++i) {
      delivery.signal();
    }
    D_--;
  }
  blockedReindeer--;
}

void Workshop::termination(unsigned int id) {
  E_--;
  if (D_ == 0 && E_ == 0) santa.signal();
  if (E_ < C && !elves.empty())
    for (; e > 0; e--)
       elves.signal();
}
