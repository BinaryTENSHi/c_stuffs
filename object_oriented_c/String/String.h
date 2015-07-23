#ifndef OBJECT_ORIENTED_C_STRING_H
#define OBJECT_ORIENTED_C_STRING_H

extern const void *String;

size_t string_length(const void *string);

void string_set(void *string,
                const char *text);

char *string_get(const void *string);

#endif //OBJECT_ORIENTED_C_STRING_H
