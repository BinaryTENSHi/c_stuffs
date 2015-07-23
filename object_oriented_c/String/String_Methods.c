#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "String.h"
#include "String.r"

size_t string_length(const void *_self) {
  const struct String *self = _self;
  assert(self);
  return strlen(self->text);
}

void string_set(void *_self,
                const char *_text) {
  struct String *self = _self;
  assert(self);
  self->text = realloc(self->text, strlen(_text) + 1);
  strncpy(self->text, _text, strlen(_text) + 1);
}

char *string_get(const void *_self) {
  const struct String *self = _self;
  assert(self);
  return self->text;
}
