#pragma once

#include <stdio.h>
#include <stdarg.h>

int store(const void *object,
          FILE *fp);

int storev(const void *object,
           va_list ap);
