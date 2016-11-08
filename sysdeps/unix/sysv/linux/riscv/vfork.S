/* Copyright (C) 2005 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/* vfork() is just a special case of clone().  */

#include <sys/asm.h>
#include <sysdep.h>
#define __ASSEMBLY__
#include <linux/sched.h>
#include <asm/signal.h>
#include <tls.h>
#include "tcb-offsets.h"

/* int vfork() */

	.text
LEAF(__libc_vfork)

	lw	t0, PID_OFFSET(tp)		/* Load the cached PID.  */
	addi	sp, sp, -16			/* Allocate stack frame.  */
	sw	t0, 0(sp)			/* Save the cached PID.  */
	neg	t0, t0				/* Negate it.  */
	bnez	t0, 1f				/* If it was zero... */
	li	t0, 0xffffffff80000000		/* use 0x80000000 instead.  */
1:	sw	t0, PID_OFFSET(tp)		/* Store the temporary PID.  */

	li	a0, (CLONE_VFORK | CLONE_VM | SIGCHLD)
	move	a1, sp
	li	a2, 0
	li	a3, 0
	li	a4, 0

	/* Do the system call */
	li	a7, __NR_clone
	scall

	lw	t0, 0(sp)			/* Load the saved PID.  */
	addi	sp, sp, 16			/* Deallocate stack frame.  */
	beqz	a0, 1f				/* If we are the parent... */
	sw	t0, PID_OFFSET(tp)		/* Restore the PID.  */
1:	bltz	a0, L(error)
	ret

	/* Something bad happened -- no child created.  */
L(error):
	j		__syscall_error

	END(__libc_vfork)

#if IS_IN (libc)
weak_alias (__libc_vfork, vfork)
strong_alias (__libc_vfork, __vfork)
libc_hidden_def (__vfork)
#endif
