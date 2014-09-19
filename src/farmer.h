#ifndef FARMER_H
#define FARMER_H

typedef enum { NORTH, SOUTH } direction;
typedef struct Farmer farmer_t;
struct Farmer {
  int id;
  direction direction;
};

#endif