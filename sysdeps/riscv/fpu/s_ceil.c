/* Copyright (C) 2017 Free Software Foundation, Inc.
   Contributed by Andrew Waterman (andrew@sifive.com).
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library.  If not, see
   <http://www.gnu.org/licenses/>.  */

#if __riscv_flen >= 64 && __riscv_xlen >= 64

#include <math.h>
#include <fpu_control.h>

double
__ceil (double x)
{
  int flags, nan;
  double mag;

  _FPU_GETFLAGS (flags);

  nan = isnan (x);
  mag = fabs (x);

  if (nan)
    return x + x;

  if (mag < (1ULL << __DBL_MANT_DIG__))
    {
      long i;
      double new_x;

      asm volatile ("fcvt.l.d %0, %1, rup" : "=r" (i) : "f" (x));
      asm volatile ("fcvt.d.l %0, %1, rup" : "=f" (new_x) : "r" (i));

      /* ceil(-0) == -0, and in general we'll always have the same
	 sign as our input.  */
      x = copysign (new_x, x);

      _FPU_SETFLAGS (flags);
    }

  return x;
}

weak_alias (__ceil, ceil)

#else

#if __riscv_xlen >= 64
#include <sysdeps/ieee754/dbl-64/wordsize-64/s_ceil.c>
#else
#include <sysdeps/ieee754/dbl-64/s_ceil.c>
#endif

#endif
