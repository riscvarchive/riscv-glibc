/* Low-level functions for atomic operations. RISC-V version.
   Copyright (C) 2014-2017 Free Software Foundation, Inc.
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

#ifndef _LINUX_RISCV_BITS_ATOMIC_H
#define _LINUX_RISCV_BITS_ATOMIC_H 1

#include_next <atomic-machine.h>

#ifndef __riscv_atomic

#include <sys/syscall.h>
#include <sysdep.h>

#define __arch_compare_and_exchange_val_8_acq(mem, newval, oldval) \
  (abort (), (__typeof (*mem)) 0)

#define __arch_compare_and_exchange_val_16_acq(mem, newval, oldval) \
  (abort (), (__typeof (*mem)) 0)

/* The only basic operation needed is compare and exchange.  */
#define __arch_compare_and_exchange_val_32_acq(mem, newval, oldval) \
  ({									      \
    INTERNAL_SYSCALL_DECL (__err);					      \
    (__typeof (*mem)) INTERNAL_SYSCALL (sysriscv, __err, 4,		      \
		      RISCV_ATOMIC_CMPXCHG, mem, oldval, newval);	      \
  })

#define __arch_compare_and_exchange_val_64_acq(mem, newval, oldval) \
  ({									      \
    INTERNAL_SYSCALL_DECL (__err);					      \
    (__typeof (*mem)) INTERNAL_SYSCALL (sysriscv, __err, 4,		      \
		      RISCV_ATOMIC_CMPXCHG64, mem, oldval, newval);	      \
  })

#endif /* __riscv_atomic */

#endif /* bits/atomic.h */
