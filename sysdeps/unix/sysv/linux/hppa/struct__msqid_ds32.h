/* HPPA implementation of the message struct __msqid_ds32.
   Copyright (C) 1995-2020 Free Software Foundation, Inc.
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
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

/* This is the "new" y2038 types defined after the 5.1 kernel. It allows
   the kernel to use msg_{s,r,c}time{_high} values to support a 64-bit
   time_t.  */
struct __msqid_ds32
{
  struct ipc_perm msg_perm; /* structure describing operation permission */
  __syscall_ulong_t msg_stime_high;
  __syscall_ulong_t msg_stime;  /* time of last msgsnd command */
  __syscall_ulong_t msg_rtime_high;
  __syscall_ulong_t msg_rtime;  /* time of last msgrcv command */
  __syscall_ulong_t msg_ctime_high;
  __syscall_ulong_t msg_ctime;  /* time of last change */
  __syscall_ulong_t __msg_cbytes; /* current number of bytes on queue */
  msgqnum_t msg_qnum;   /* number of messages currently on queue */
  msglen_t msg_qbytes;    /* max number of bytes allowed on queue */
  __pid_t msg_lspid;    /* pid of last msgsnd() */
  __pid_t msg_lrpid;    /* pid of last msgrcv() */
  __syscall_ulong_t __glibc_reserved4;
  __syscall_ulong_t __glibc_reserved5;
};
