#include <errno.h>
#include <math.h>
#include "fpu_control.h"

float __fdimf (float x, float y)
{
  if (islessequal (x, y))
    return 0.0;

  if (__builtin_expect (_FCLASS (x - y) & _FCLASS_INF, 0))
    errno = ERANGE;

  return x - y;
}
weak_alias (__fdimf, fdimf)
