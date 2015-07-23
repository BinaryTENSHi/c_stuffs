#include "debug.h"


int store(const void *object,
          FILE *fp) {
  return fprintf(fp, "Object @ 0x%p", object);
}

int storev(const void *object,
           va_list ap) {
  FILE *fp = va_arg(ap, FILE*);
  return store(object, fp);
}
