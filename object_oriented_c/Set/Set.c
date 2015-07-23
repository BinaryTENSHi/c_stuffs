#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

#include "Set.r"
#include "../Class.h"
#include "../new.h"

static void *Set_ctor(void *_self,
                      va_list *app) {
  printf("Set ctor\n");
  return _self;
}

static void *Set_dtor(void *_self) {
  printf("Set dtor\n");
  struct Set *self = _self;

  assert(self);

  struct SetEntry *p = self->root;
  struct SetEntry *n;
  while (p) {
    n = p->next;
    free(p);
    p = n;
  }

  self->root = NULL;
  return self;
}

static void *Set_clone(const void *_self) {
  return 0;
}

static int Set_differ(const void *_self,
                      const void *_b) {
  const struct Set *self = _self;
  const struct Set *b = _b;

  assert(self);
  assert(b);

  if (self->count != b->count)
    return b->count - self->count;

  return 0;
}

static const struct Class _Set = {
        .size = sizeof(struct Set),
        .ctor = Set_ctor,
        .dtor = Set_dtor,
        .clone = Set_clone,
        .differ = Set_differ
};

const void *Set = &_Set;
