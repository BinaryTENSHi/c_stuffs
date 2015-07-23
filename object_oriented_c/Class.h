#ifndef OBJECT_ORIENTED_C_CLASS_H
#define OBJECT_ORIENTED_C_CLASS_H

#include <stddef.h>
#include <stdarg.h>

struct Class {
  size_t size;

  void *(*ctor)(void *self,
                va_list *app);

  void *(*dtor)(void *self);

  void *(*clone)(const void *self);

  int (*differ)(const void *self,
                const void *b);
};

#endif //OBJECT_ORIENTED_C_CLASS_H
