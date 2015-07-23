#include <assert.h>
#include <stdarg.h>
#include <malloc.h>

#include "Set.h"
#include "Set.r"

void *set_add(void *_set,
              const void *_element) {
  struct Set *set = _set;
  assert(set);

  struct SetEntry *curr = set->root;
  struct SetEntry *prev = curr;
  while (curr) {
    prev = curr;
    curr = curr->next;
  }

  ++set->count;
  curr = malloc(sizeof(struct SetEntry));
  curr->element = (void *) _element;
  curr->next = NULL;

  if (!prev)
    set->root = curr;
  else
    prev->next = curr;

  return curr->element;
}

void *set_find(const void *_set,
               const void *_element) {
  const struct Set *set = _set;
  assert(set);

  struct SetEntry *p = set->root;
  while (p) {
    if (p->element == _element)
      return p;

    p = p->next;
  }

  return NULL;
}

int set_contains(const void *_set,
                 const void *_element) {
  return set_find(_set, _element) != 0;
}

void *set_drop(void *_set,
               const void *_element) {
  struct Set *set = _set;

  struct SetEntry *curr = set->root;
  struct SetEntry *prev = curr;

  while (curr) {
    if (curr->element == _element)
      break;

    prev = curr;
    curr = curr->next;
  }

  void *ret = NULL;
  if (prev && curr) {
    prev->next = curr->next;
    --set->count;
    ret = curr->element;
  }

  free(curr);
  return ret;
}

unsigned set_count(const void *_set) {
  const struct Set *set = _set;
  assert(set);
  return set->count;
}

int set_apply(const void *set,
              int (*action)(void *,
                            va_list),
              ...) {
  return 0;
}


