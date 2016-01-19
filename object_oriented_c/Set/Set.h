#pragma once

extern const void *Set;

void *set_add(void *set,
              const void *element);

void *set_find(const void *set,
               const void *element);

void *set_drop(void *set,
               const void *element);

int set_contains(const void *set,
                 const void *element);

unsigned set_count(const void *set);

int set_apply(const void *set,
              int (*action)(void *object,
                            va_list ap),
              ...);
