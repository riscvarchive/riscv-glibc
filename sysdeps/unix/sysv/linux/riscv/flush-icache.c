/* RISC-V instruction cache flushing VDSO calls
   Copyright (C) 2017 Free Software Foundation, Inc.

   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <dl-vdso.h>
#include <stdlib.h>
#include <atomic.h>
#include <sys/cachectl.h>

typedef int (*func_type) (void *, void *, unsigned long);

static func_type
__lookup_riscv_flush_icache (void)
{
  PREPARE_VERSION_KNOWN (linux_version, LINUX_4_15);

  func_type func = _dl_vdso_vsym ("__vdso_flush_icache", &linux_version);

  /* The vDSO is required, as there is no exposed system call equivalent.  */
  if (!func)
    abort ();

  return func;
}

#ifdef SHARED

#define INIT_ARCH()
libc_ifunc (__riscv_flush_icache, __lookup_riscv_flush_icache ())

#else

int
__riscv_flush_icache (void *start, void *end, unsigned long flags)
{
  static volatile func_type cached_func;

  func_type func = cached_func;

  if (!func)
    cached_func = func = __lookup_riscv_flush_icache ();

  return func (start, end, flags);
}

#endif
