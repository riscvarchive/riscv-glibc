#if __riscv_flen >= 64
#include "math.h"

double __copysign(double x, double y)
{
  double res;
  asm ("fsgnj.d %0, %1, %2" : "=f"(res) : "f"(x), "f"(y));
  return res;
}
weak_alias (__copysign, copysign)
#else
#include <sysdeps/ieee754/dbl-64/s_copysign.c>
#endif
