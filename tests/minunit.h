/* file: minunit.h */
#ifndef MINUNIT_H
#define MINUNIT_H
#include <stdio.h>

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                              if (message) return message; } while (0)
#define mu_assert_equals_int(message, expected, actual) \
                          do { \
                            if (!(expected == actual)) { \
                            	sprintf(message, \
                            		"%s (Expected: %d, Actual: %d)", \
                            		message, expected, actual); \
                            	return message; \
                            } \
                          } while (0)

extern int tests_run;

 #endif