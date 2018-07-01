#include <x86intrin.h>

unsigned short float_to_half(float f) {
  unsigned short us = _cvtss_sh(f, 0);
  return us;
}

