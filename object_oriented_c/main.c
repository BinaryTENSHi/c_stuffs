#include "new.h"
#include "String/String.h"
#include "Set/Set.h"

int main(int argc,
         char *argv[]) {
  void *a = new(String, "a");
  void *b = new(String, "bbb");
  void *s = new(Set);

  printf("LENGTH A: %lu\n", string_length(a));
  printf("LENGTH B: %lu\n", string_length(b));

  printf("Prev: %s\n", string_get(a));
  string_set(a, "New String");
  printf("New:  %s\n", string_get(a));

  set_add(s, a);
  set_add(s, b);

  printf("CONTAINS A: %u\n", set_contains(s, a));
  printf("CONTAINS B: %u\n", set_contains(s, b));

  printf("DROP B: %p\n", set_drop(s, b));
  printf("DROP B: %p\n", set_drop(s, b));

  printf("ADD B: %p\n", set_add(s, b));

  delete(s);
  delete(a);
  delete(b);

  return 0;
}