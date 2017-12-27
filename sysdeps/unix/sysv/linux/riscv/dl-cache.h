/* Support for reading /etc/ld.so.cache files written by Linux ldconfig.
   Copyright (C) 2003-2018 Free Software Foundation, Inc.
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

#include <ldconfig.h>

/* For now we only support the natural XLEN ABI length on all targets, so the
   only bits that need to go into ld.so.cache are the FLEG ABI length.  */
#if defined __riscv_float_abi_double
# define _DL_CACHE_DEFAULT_ID    (FLAG_RISCV_FLOAT_ABI_DOUBLE | FLAG_ELF_LIBC6)
#else
# define _DL_CACHE_DEFAULT_ID    (FLAG_RISCV_FLOAT_ABI_SOFT | FLAG_ELF_LIBC6)
#endif

#define _dl_cache_check_flags(flags)                    \
  ((flags) == _DL_CACHE_DEFAULT_ID)

#include_next <dl-cache.h>
