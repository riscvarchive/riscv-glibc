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

#if __riscv_flen >= 64

#include "math.h"
#include "fpu_control.h"

int
__issignaling (double x)
{
  return _FCLASS (x) & _FCLASS_SNAN;
}
libm_hidden_def (__issignaling)

#else

#if __riscv_xlen >= 64
#include <sysdeps/ieee754/dbl-64/wordsize-64/s_issignaling.c>
#else
#include <sysdeps/ieee754/dbl-64/s_issignaling.c>
#endif

#endif
