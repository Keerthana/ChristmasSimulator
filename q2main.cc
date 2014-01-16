#include "q2santa.h"
#include "q2elf.h"
#include "q2reindeer.h"
MPRNG mprng;

extern void usage(char *argv[]);

void uMain::main() {
  // Bound on number of times Reindeer gets served ahead of Elves
  unsigned int N = 3;
  // Number of Elves
  unsigned int E = 3;
  // Seed for Random number generator
  unsigned int seed = time(NULL) ^ getpid();
  // Number of times Elves wants to consult Santa
  unsigned int C = 3;
  // Number of times reindeer wants to deliver toys
  unsigned int D = 3;
  // Number of reindeers
  unsigned int R = Reindeer::MAX_NUM_REINDEER;
  switch (argc) {
  case 6:
    if (atoi(argv[5]) <= 0)
      usage(argv);
    D = atoi(argv[5]);
  case 5:
    if (atoi(argv[4]) < 0)
      usage(argv);
    C = atoi(argv[4]);
  case 4:
    if (atoi(argv[3]) < 1)
      usage(argv);
    seed = atoi(argv[3]);
    mprng.seed(seed);
  case 3:
    if (atoi(argv[2]) < 1)
      usage(argv);
    E = atoi(argv[2]);
  case 2:
    if (atoi(argv[1]) < 1) {
      usage(argv);
    }
    N = atoi(argv[1]);
  case 1:
    break;
  default:
    usage(argv);
  }

  // Setting up Drøbak
  Printer myPrinter(E);
  Workshop myWorkshop(myPrinter, N, E, D);

  Santa *mySanta = new Santa(myWorkshop, myPrinter);
  Elf *myElf[E];
  for (unsigned int i = 0; i < E; ++i) {
    myElf[i] = new Elf(i, myWorkshop, myPrinter, C);
  }
  Reindeer *myReindeer[R];
  for (unsigned int i = 0; i < R; ++i) {
    myReindeer[i] = new Reindeer(i + E, myWorkshop, myPrinter, D);
  }

  delete mySanta;
  for (unsigned int i = 0; i < E; ++i) {
    delete myElf[i];
  }
  for (unsigned int i = 0; i < R; ++i) {
    delete myReindeer[i];
  }
}
