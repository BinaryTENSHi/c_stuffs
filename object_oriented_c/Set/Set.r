#pragma once

struct Set {
  const void *class;
  unsigned count;
  struct SetEntry *root;
};

struct SetEntry {
  void *element;
  struct SetEntry *next;
};
