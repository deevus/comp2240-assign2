#ifndef NODE_H
#define NODE_H

typedef struct Node node_t;
struct Node {
  void *data;
  node_t *nextptr;
};

void node_init(node_t *node, void *data);

#endif /* NODE_H */