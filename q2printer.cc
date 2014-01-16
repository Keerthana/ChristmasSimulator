#include <uC++.h>
#include "q2printer.h"
using namespace std;

void usage(char *argv[]) {
  cerr << "Usage: " << argv[0]
       << " [ N (> 0) [ E (> 0) [ Seed (> 0) [ C (>= 0) [ D (>= 0) ] ] ] ] ]"
       << endl;
  exit(EXIT_FAILURE);
}

Printer::Printer(const unsigned int MAX_NUM_ELVES)
    : nElves(MAX_NUM_ELVES), nIds(1 + nElves + 5),
      flushData(new FlushData[nIds]) {
  for (unsigned int i = 0; i < nIds; i++) {
    flushData[i].hasData = false;
    flushData[i].numBlocked = 0;
  }

  for (unsigned int i = 0; i < nIds; ++i) {
    if (i == 0)
      cout << "Sa\t"; // Santa
    else if (i > 0 && i <= nElves)
      cout << "E"; // Elf
    else
      cout << "R"; // Reindeer
    if (i > 0)
      cout << i << "\t";
  }
  cout << endl;
  for (unsigned int i = 0; i < nIds; ++i) {
    cout << "--\t";
  }
  cout << endl;
}

Printer::~Printer() {
  cout << "Workshop closed" << endl;
  delete[] flushData;
}

void Printer::print(unsigned int id, States state) {
  // Flush data, if it is over-written
  if (flushData[id].hasData) {
    resume();
  }

  if (state == Finished) {
    printFinished(id);
    return;
  }
  flushData[id].hasData = true;
  flushData[id].state = state;
}

void Printer::print(unsigned int id, States state, unsigned int numBlocked) {
  // Flush data if it is over-written or if task finishes
  print(id, state);
  flushData[id].numBlocked = numBlocked;
}

void Printer::printFinished(unsigned int id) {
    for (unsigned int i = 0; i < nIds; ++i) {
        if (i == id) {
            cout << "F";
        } else {
            cout << "...";
        }
        cout << "\t";
    }
    cout << endl;
}

void Printer::main() {
  for (;;) {
   for (unsigned int i = 0; i < nIds; ++i) {
    if (flushData[i].hasData) {
      cout << static_cast<char>(flushData[i].state);
      if (flushData[i].numBlocked > 0) {
        cout << " " << flushData[i].numBlocked;
      }
    }
    cout << "\t";
    flushData[i].hasData = false;
    flushData[i].numBlocked = 0;
  }
  cout << endl;
  suspend();
  }
}
