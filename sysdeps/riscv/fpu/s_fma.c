#if __riscv_flen >= 64
#include <math.h>
#include <fenv.h>
#include <ieee754.h>

double __fma (double x, double y, double z)
{
  double out;
  asm volatile ("fmadd.d %0, %1, %2, %3" : "=f"(out) : "f"(x), "f"(y), "f"(z));
  return out;
}
weak_alias (__fma, fma)
#else
#include <sysdeps/ieee754/dbl-64/s_fma.c>
#endif
