#if __riscv_flen >= 64
#include "math.h"

double __fabs(double x)
{
  double res;
  asm ("fabs.d %0, %1" : "=f"(res) : "f"(x));
  return res;
}
weak_alias (__fabs, fabs)
#else
#include <sysdeps/ieee754/dbl-64/s_fabs.c>
#endif
