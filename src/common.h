#ifndef COMMON_H
#define COMMON_H 

extern void common_init(int north_farmers, int south_farmers, void *fn);

extern void common_clean_up();

extern void common_pthread_setcancel();

#endif