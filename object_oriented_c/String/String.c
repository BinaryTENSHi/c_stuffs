#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "String.h"
#include "String.r"
#include "../Class.h"
#include "../new.h"

static void *String_ctor(void *_self,
                         va_list *app) {
  printf("String ctor\n");
  struct String *self = _self;
  const char *text = va_arg(*app, const char*);
  self->text = malloc(strlen(text) + 1);
  assert(self->text);
  strncpy(self->text, text, strlen(text) + 1);
  return self;
}

static void *String_dtor(void *_self) {
  printf("String dtor\n");
  struct String *self = _self;
  free(self->text);
  self->text = 0;
  return self;
}

static void *String_clone(const void *_self) {
  struct String *self = (void *) _self;
  return new(String, self->text);
}

static int String_differ(const void *_self,
                         const void *_b) {
  const struct String *self = _self;
  const struct String *b = _b;

  if (self == b)
    return 0;

  if (!b || b->class != String)
    return 1;

  return strcmp(self->text, b->text);
}

static const struct Class _String = {
        .size = sizeof(struct String),
        .ctor = String_ctor,
        .dtor = String_dtor,
        .clone = String_clone,
        .differ = String_differ
};

const void *String = &_String;
