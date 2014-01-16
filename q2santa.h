#ifndef Q2SANTA_H
#define Q2SANTA_H
#include "q2workshop.h"

_Task Santa {
  // private members go here
  void main();

public:
  Santa(Workshop & wrk, Printer & prt);

private:
  Workshop *wrk_;
  Printer *prt_;
  unsigned int id_;
  Workshop::Status status;
}
;

#endif // Q2SANTA_H
