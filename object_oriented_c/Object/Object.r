#ifndef OBJECT_ORIENTED_C_OBJECT_R
#define OBJECT_ORIENTED_C_OBJECT_R

struct Object {
  const void *class;
  unsigned count;
  struct Set *in;
};

#endif //OBJECT_ORIENTED_C_OBJECT_R