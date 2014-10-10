/**
  Simon Hartcher
  C3185790

  COMP2240 Assignment 2
**/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#if Q1 
#include "question1.h"
#elif Q2
#include "question2.h"
#elif Q3
#include "question3.h"
#else
#include "question4.h"
#endif

#define clear_screen() (system("clear"))

static char *usage_str = "Usage: ./qN [#North Farmers] [#South Farmers]. Example: ./q4 6 4\r\n";

int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf(usage_str);
  }
  else {
    /* normal execution */
    int south = atoi(argv[argc - 1]);
    int north = atoi(argv[argc - 2]);

    if (north + south == 0) {
      printf(usage_str);
    }

    //setup interrupt signal
    signal(SIGINT, clean_up);

    //run the program
    //this will block until threads have finished
    run(north, south);

    //exit when done
    exit(EXIT_SUCCESS);
  }

}
