#include "math.h"

float
__copysignf (float x, float y)
{
  asm ("fsgnj.s %0, %1, %2" : "=f" (x) : "f" (x), "f" (y));
  return x;
}
weak_alias (__copysignf, copysignf)
