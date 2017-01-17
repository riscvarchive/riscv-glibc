/* Copyright (C) 2011-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Chris Metcalf <cmetcalf@tilera.com>, 2011.

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

#ifndef _MATH_H
# error "Never use <bits/mathinline.h> directly; include <math.h> instead."
#endif

#ifndef __extern_always_inline
# define __MATH_INLINE __inline
#else
# define __MATH_INLINE __extern_always_inline
#endif


#if defined __USE_ISOC99 && defined __GNUC__

/* Test for negative number.  Used in the signbit() macro.  */
__MATH_INLINE int
__NTH (__signbitf (float __x))
{
  return __builtin_signbitf (__x);
}
__MATH_INLINE int
__NTH (__signbit (double __x))
{
  return __builtin_signbit (__x);
}

/* Leave it to the compiler to optimize these if __NO_MATH_ERRNO__.  */
# if defined __riscv_flen && !defined __NO_MATH_ERRNO__

#  if __riscv_xlen >= 64

__MATH_INLINE long long int
__NTH (llrintf (float __x))
{
  long long int __res;
  __asm__ __volatile__ ("fcvt.l.s %0, %1" : "=r" (__res) : "f" (__x));
  return __res;
}

__MATH_INLINE long long int
__NTH (llroundf (float __x))
{
  long long int __res;
  __asm__ __volatile__ ("fcvt.l.s %0, %1, rmm" : "=r" (__res) : "f" (__x));
  return __res;
}

#  endif /* __riscv_xlen >= 64 */

__MATH_INLINE long int
__NTH (lrintf (float __x))
{
#ifdef __LP64__
  return (long int) llrintf (__x);
#else
  long int __res;
  __asm__ __volatile__ ("fcvt.w.s %0, %1" : "=r" (__res) : "f" (__x));
  return __res;
#endif
}

__MATH_INLINE long int
__NTH (lroundf (float __x))
{
#ifdef __LP64__
  return (long int) llroundf (__x);
#else
  long int __res;
  __asm__ __volatile__ ("fcvt.w.s %0, %1, rmm" : "=r" (__res) : "f" (__x));
  return __res;
#endif
}

# endif /* __riscv_flen && !__NO_MATH_ERRNO__ */

/* Leave it to the compiler to optimize these if __NO_MATH_ERRNO__.  */
# if defined __riscv_flen && __riscv_flen >= 64 && !defined __NO_MATH_ERRNO__

#  if __riscv_xlen >= 64

__MATH_INLINE long long int
__NTH (llrint (double __x))
{
  long long int __res;
  __asm__ __volatile__ ("fcvt.l.d %0, %1" : "=r" (__res) : "f" (__x));
  return __res;
}

__MATH_INLINE long long int
__NTH (llround (double __x))
{
  long long int __res;
  __asm__ __volatile__ ("fcvt.l.d %0, %1, rmm" : "=r" (__res) : "f" (__x));
  return __res;
}

#  endif /* __riscv_xlen >= 64 */

__MATH_INLINE long int
__NTH (lrint (double __x))
{
#ifdef __LP64__
  return (long int) llrint (__x);
#else
  long int __res;
  __asm__ __volatile__ ("fcvt.w.d %0, %1" : "=r" (__res) : "f" (__x));
  return __res;
#endif
}

__MATH_INLINE long int
__NTH (lround (double __x))
{
#ifdef __LP64__
  return (long int) llround (__x);
#else
  long int __res;
  __asm__ __volatile__ ("fcvt.w.d %0, %1, rmm" : "=r" (__res) : "f" (__x));
  return __res;
#endif
}

# endif /* __riscv_flen >= 64 && !__NO_MATH_ERRNO__ */

#endif
