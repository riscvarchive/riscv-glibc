/* RISC-V PLT trampoline
   Copyright (C) 2017-2018 Free Software Foundation, Inc.

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

#include <sysdep.h>
#include <sys/asm.h>

/* Assembler veneer called from the PLT header code for lazy loading.
   The PLT header passes its own args in t0-t2.  */

#define FRAME_SIZE (-((-10 * SZREG) & ALMASK))

ENTRY (_dl_runtime_resolve)
  # Save arguments to stack.
  addi sp, sp, -FRAME_SIZE
  REG_S ra, 9*SZREG(sp)
  REG_S a0, 1*SZREG(sp)
  REG_S a1, 2*SZREG(sp)
  REG_S a2, 3*SZREG(sp)
  REG_S a3, 4*SZREG(sp)
  REG_S a4, 5*SZREG(sp)
  REG_S a5, 6*SZREG(sp)
  REG_S a6, 7*SZREG(sp)
  REG_S a7, 8*SZREG(sp)

  # Update .got.plt and obtain runtime address of callee.
  slli a1, t1, 1
  mv a0, t0       # link map
  add a1, a1, t1  # reloc offset (== thrice the .got.plt offset)
  la a2, _dl_fixup
  jalr a2
  mv t1, a0

  # Restore arguments from stack.
  REG_L ra, 9*SZREG(sp)
  REG_L a0, 1*SZREG(sp)
  REG_L a1, 2*SZREG(sp)
  REG_L a2, 3*SZREG(sp)
  REG_L a3, 4*SZREG(sp)
  REG_L a4, 5*SZREG(sp)
  REG_L a5, 6*SZREG(sp)
  REG_L a6, 7*SZREG(sp)
  REG_L a7, 8*SZREG(sp)
  addi sp, sp, FRAME_SIZE

  # Invoke the callee.
  jr t1
END (_dl_runtime_resolve)
