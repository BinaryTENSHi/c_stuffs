#ifndef OBJECT_ORIENTED_C_DEBUG_H
#define OBJECT_ORIENTED_C_DEBUG_H

#include <stdio.h>
#include <stdarg.h>

int store(const void *object,
          FILE *fp);

int storev(const void *object,
           va_list ap);

#endif //OBJECT_ORIENTED_C_DEBUG_H
