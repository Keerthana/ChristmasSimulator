#ifndef Q2ELF_H
#define Q2ELF_H
#include "q2workshop.h"

_Task Elf {
  void main();

public:
  // number of elves for a consultation with Santa
  enum { CONSULTING_GROUP_SIZE = 3 };
  Elf(unsigned int id, Workshop & wrk, Printer & prt,
      unsigned int numConsultations);

private:
  unsigned int id_;
  Workshop *wrk_;
  Printer *prt_;
  unsigned int numConsultations_;
  bool isConsulting;
}
;

#endif // Q2ELF_H
