#pragma once

extern const void *String;

size_t string_length(const void *string);

void string_set(void *string,
                const char *text);

char *string_get(const void *string);
