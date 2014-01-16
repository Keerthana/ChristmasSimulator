#ifndef Q2PRINTER_H
#define Q2PRINTER_H
#include <uC++.h>
#include <iostream>
#include <string>
#include <sstream>

#include "MPRNG.h"

extern MPRNG mprng;

_Cormonitor Printer { // choose _Monitor or  _Cormonitor
public:
  enum States {
    Starting = 'S',
    Blocked = 'B', // general
    Unblocked = 'U',
    Finished = 'F', // general
    Napping = 'N',
    Awake = 'A', // Santa
    Working = 'W',
    NeedHelp = 'H', // elf
    OnVacation = 'V',
    CheckingIn = 'I', // reindeer
    DeliveringToys = 'D',
    DoneDelivering = 'd', // Santa, reindeer
    Consulting = 'C',
    DoneConsulting = 'c',   // Santa, elves
    ConsultingFailed = 'X', // elf
  };
  Printer(const unsigned int MAX_NUM_ELVES);
  ~Printer();
  void print(unsigned int id, States state);
  void print(unsigned int id, States state, unsigned int numBlocked);

private:
  unsigned int nElves;
  unsigned int nIds;

  struct FlushData {
    bool hasData;
    States state;
    unsigned int numBlocked;
  };
  FlushData *flushData;
  void printFinished(unsigned int finishedId);

  void main();
}
;
#endif // Q2PRINTER_H
