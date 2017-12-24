/* struct ucontext definition, RISC-V version.
   Copyright (C) 1997-2017 Free Software Foundation, Inc.  
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

/* Don't rely on this, the interface is currently messed up and may need to
   be broken to be fixed.  */
#ifndef _SYS_UCONTEXT_H
#define _SYS_UCONTEXT_H	1

#include <features.h>

#include <bits/types/sigset_t.h>
#include <bits/types/stack_t.h>
#include <asm/ptrace.h>

#ifdef __USE_MISC
# define __ctx(fld) fld
#else
# define __ctx(fld) __ ## fld
#endif

#ifdef __USE_MISC

#define NGREG	32

#define REG_PC 0
#define REG_RA 1
#define REG_SP 2
#define REG_TP 4
#define REG_S0 8
#define REG_A0 10
#define REG_NARGS 8

typedef unsigned long greg_t;

/* Container for all general registers.  */
typedef greg_t gregset_t[NGREG];

/* Container for floating-point state.  */
typedef union __riscv_fp_state fpregset_t;

#endif

/* These structures all must match what's in Linux.  Some are copied.  */
struct __riscv_gp_state {
  unsigned long pc;
  unsigned long ra;
  unsigned long sp;
  unsigned long gp;
  unsigned long tp;
  unsigned long t0;
  unsigned long t1;
  unsigned long t2;
  unsigned long s0;
  unsigned long s1;
  unsigned long a0;
  unsigned long a1;
  unsigned long a2;
  unsigned long a3;
  unsigned long a4;
  unsigned long a5;
  unsigned long a6;
  unsigned long a7;
  unsigned long s2;
  unsigned long s3;
  unsigned long s4;
  unsigned long s5;
  unsigned long s6;
  unsigned long s7;
  unsigned long s8;
  unsigned long s9;
  unsigned long s10;
  unsigned long s11;
  unsigned long t3;
  unsigned long t4;
  unsigned long t5;
  unsigned long t6;
};

typedef struct mcontext_t
  {
    union {
      struct __riscv_gp_state byname;
      unsigned long byindex[32];
    } gregs;
    union  __riscv_fp_state fpregs;
  } mcontext_t;

/* Userlevel context.  */
typedef struct ucontext_t
  {
    unsigned long      uc_flags;
    struct ucontext_t *uc_link;
    stack_t            uc_stack;
    sigset_t           uc_sigmask;
    /* There's some padding here to allow sigset_t to be expanded in the
     * future.  Though this is unlikely, other architectures put uc_sigmask
     * at the end of this structure and explicitly state it can be
     * expanded, so we didn't want to box ourselves in here. */
    __u8               __unused[1024 / 8 - sizeof (sigset_t)];
    /* We can't put uc_sigmask at the end of this structure because we need
     * to be able to expand sigcontext in the future.  For example, the
     * vector ISA extension will almost certainly add ISA state.  We want
     * to ensure all user-visible ISA state can be saved and restored via a
     * ucontext, so we're putting this at the end in order to allow for
     * infinite extensibility.  Since we know this will be extended and we
     * assume sigset_t won't be extended an extreme amount, we're
     * prioritizing this. */
    mcontext_t uc_mcontext;
  } ucontext_t;

#endif /* sys/ucontext.h */
