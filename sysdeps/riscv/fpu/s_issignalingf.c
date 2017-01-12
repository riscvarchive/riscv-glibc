#include "math.h"
#include "fpu_control.h"

int
__issignalingf (float x)
{
  return _FCLASS (x) & _FCLASS_SNAN;
}
libm_hidden_def (__issignalingf)
