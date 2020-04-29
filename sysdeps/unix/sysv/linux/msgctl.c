/* Copyright (C) 1995-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@gnu.ai.mit.edu>, August 1995.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <sys/msg.h>
#include <ipc_priv.h>
#include <sysdep.h>
#include <shlib-compat.h>
#include <errno.h>
#include <struct__msqid_ds32.h>
#include <linux/posix_types.h>  /* For __kernel_mode_t.  */

#ifndef DEFAULT_VERSION
# ifndef __ASSUME_SYSVIPC_BROKEN_MODE_T
#  define DEFAULT_VERSION GLIBC_2_2
# else
#  define DEFAULT_VERSION GLIBC_2_31
# endif
#endif

static int
msgctl_syscall (int msqid, int cmd, struct msqid_ds *buf)
{
  int ret;
#if __IPC_TIME64
  /* A temporary buffer is used to avoid both an issue where the export
     semid_ds might not follow the kernel's expected layout (due
     to {s,r,c}time{_high} alignment in 64-bit time case) and the issue where
     some kernel versions might not clear the high bits when returning
     then {s,r,c}time{_high} information.  */
  struct __msqid_ds32 tmp;
  struct msqid_ds *orig;
  bool restore = false;

  if (cmd == IPC_STAT || cmd == MSG_STAT || cmd == MSG_STAT_ANY)
    {
      tmp = (struct __msqid_ds32) {
        .msg_perm  = buf->msg_perm,
        .msg_stime = buf->msg_stime,
        .msg_stime_high = buf->msg_stime >> 32,
        .msg_rtime = buf->msg_rtime,
        .msg_rtime_high = buf->msg_rtime >> 32,
        .msg_ctime = buf->msg_ctime,
        .msg_ctime_high = buf->msg_ctime >> 32,
        .__msg_cbytes = buf->__msg_cbytes,
        .msg_qnum = buf->msg_qnum,
        .msg_qbytes = buf->msg_qbytes,
        .msg_lspid = buf->msg_lspid,
        .msg_lrpid = buf->msg_lrpid,
      };
      orig = buf;
      buf = (struct msqid_ds*) &tmp;
      restore = true;
    }
#endif

#ifdef __ASSUME_DIRECT_SYSVIPC_SYSCALLS
  ret = INLINE_SYSCALL_CALL (msgctl, msqid, cmd | __IPC_64, buf);
#else
  ret = INLINE_SYSCALL_CALL (ipc, IPCOP_msgctl, msqid, cmd | __IPC_64, 0,
                             buf);
#endif

#if __IPC_TIME64
  if (ret >= 0 && restore)
    {
      buf = orig;

      buf->msg_perm  = tmp.msg_perm;
      buf->msg_stime = tmp.msg_stime
                           | ((time_t) tmp.msg_stime_high << 32);
      buf->msg_rtime = tmp.msg_rtime
                           | ((time_t) tmp.msg_rtime_high << 32);
      buf->msg_ctime = tmp.msg_ctime
                           | ((time_t) tmp.msg_ctime_high << 32);
      buf->__msg_cbytes = tmp.__msg_cbytes;
      buf->msg_qnum = tmp.msg_qnum;
      buf->msg_qbytes = tmp.msg_qbytes;
      buf->msg_lspid = tmp.msg_lspid;
      buf->msg_lrpid = tmp.msg_lrpid;
    }
#endif

    return ret;
}

int
__new_msgctl (int msqid, int cmd, struct msqid_ds *buf)
{
  /* POSIX states ipc_perm mode should have type of mode_t.  */
  _Static_assert (sizeof ((struct msqid_ds){0}.msg_perm.mode)
		  == sizeof (mode_t),
		  "sizeof (msqid_ds.msg_perm.mode) != sizeof (mode_t)");

#ifdef __ASSUME_SYSVIPC_BROKEN_MODE_T
  struct msqid_ds tmpds;
  if (cmd == IPC_SET)
    {
      tmpds = *buf;
      tmpds.msg_perm.mode *= 0x10000U;
      buf = &tmpds;
    }
#endif

  int ret = msgctl_syscall (msqid, cmd, buf);

  if (ret >= 0)
    {
      switch (cmd)
	{
	case IPC_STAT:
	case MSG_STAT:
	case MSG_STAT_ANY:
#ifdef __ASSUME_SYSVIPC_BROKEN_MODE_T
	  buf->msg_perm.mode >>= 16;
#else
	  /* Old Linux kernel versions might not clear the mode padding.  */
	  if (sizeof ((struct msqid_ds){0}.msg_perm.mode)
	      != sizeof (__kernel_mode_t))
	    buf->msg_perm.mode &= 0xFFFF;
#endif
	}
    }

  return ret;
}
versioned_symbol (libc, __new_msgctl, msgctl, DEFAULT_VERSION);

#if defined __ASSUME_SYSVIPC_BROKEN_MODE_T \
    && SHLIB_COMPAT (libc, GLIBC_2_2, GLIBC_2_31)
int
attribute_compat_text_section
__msgctl_mode16 (int msqid, int cmd, struct msqid_ds *buf)
{
  return msgctl_syscall (msqid, cmd, buf);
}
compat_symbol (libc, __msgctl_mode16, msgctl, GLIBC_2_2);
#endif

#if SHLIB_COMPAT (libc, GLIBC_2_0, GLIBC_2_2)
struct __old_msqid_ds
{
  struct __old_ipc_perm msg_perm;	/* structure describing operation permission */
  struct msg *__msg_first;		/* pointer to first message on queue */
  struct msg *__msg_last;		/* pointer to last message on queue */
  __time_t msg_stime;			/* time of last msgsnd command */
  __time_t msg_rtime;			/* time of last msgrcv command */
  __time_t msg_ctime;			/* time of last change */
  struct wait_queue *__wwait;		/* ??? */
  struct wait_queue *__rwait;		/* ??? */
  unsigned short int __msg_cbytes;	/* current number of bytes on queue */
  unsigned short int msg_qnum;		/* number of messages currently on queue */
  unsigned short int msg_qbytes;	/* max number of bytes allowed on queue */
  __ipc_pid_t msg_lspid;		/* pid of last msgsnd() */
  __ipc_pid_t msg_lrpid;		/* pid of last msgrcv() */
};

int
attribute_compat_text_section
__old_msgctl (int msqid, int cmd, struct __old_msqid_ds *buf)
{
#if defined __ASSUME_DIRECT_SYSVIPC_SYSCALLS \
    && !defined __ASSUME_SYSVIPC_DEFAULT_IPC_64
  /* For architecture that have wire-up msgctl but also have __IPC_64 to a
     value different than default (0x0) it means the compat symbol used the
     __NR_ipc syscall.  */
  return INLINE_SYSCALL_CALL (msgctl, msqid, cmd, buf);
#else
  return INLINE_SYSCALL_CALL (ipc, IPCOP_msgctl, msqid, cmd, 0, buf);
#endif
}
compat_symbol (libc, __old_msgctl, msgctl, GLIBC_2_0);
#endif
