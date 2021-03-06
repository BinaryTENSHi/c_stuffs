#pragma once

#include <stdio.h>
#include <stdarg.h>

void *new(const void *type,
          ...);

void delete(void *item);

int differ(const void *self,
           const void *b);

void *clone(const void *self);

size_t sizeOf(const void *self);
