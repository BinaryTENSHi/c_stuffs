#pragma once

struct Object {
  const void *class;
  unsigned count;
  struct Set *in;
};
