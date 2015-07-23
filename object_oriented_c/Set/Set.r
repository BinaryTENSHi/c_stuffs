#ifndef OBJECT_ORIENTED_C_SET_R
#define OBJECT_ORIENTED_C_SET_R

struct Set {
  const void *class;
  unsigned count;
  struct SetEntry *root;
};

struct SetEntry {
  void *element;
  struct SetEntry *next;
};

#endif //OBJECT_ORIENTED_C_SET_R