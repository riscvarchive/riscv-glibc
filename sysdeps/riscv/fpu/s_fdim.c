#if __riscv_flen >= 64
#include <errno.h>
#include <math.h>
#include "fpu_control.h"

double __fdim (double x, double y)
{
  if (islessequal (x, y))
    return 0.0;

  if (__builtin_expect (_FCLASS (x - y) & _FCLASS_INF, 0))
    errno = ERANGE;

  return x - y;
}
weak_alias (__fdim, fdim)
#else
#include <math/s_fdim.c>
#endif
