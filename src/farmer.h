#ifndef FARMER_H
#define FARMER_H

typedef enum { NORTH, SOUTH, WEST } direction;
typedef struct Farmer farmer_t;
struct Farmer {
  int id;
  direction direction;
};

#endif