/* Copyright (C) 1999-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Andreas Jaeger <aj@suse.de>, 1999 and
		  Jakub Jelinek <jakub@redhat.com>, 1999.

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
   <http://www.gnu.org/licenses/>.  */


int process_elf32_file (const char *file_name, const char *lib, int *flag,
			unsigned int *osversion, char **soname,
			void *file_contents, size_t file_length);
int process_elf64_file (const char *file_name, const char *lib, int *flag,
			unsigned int *osversion, char **soname,
			void *file_contents, size_t file_length);

#define SUPPORTED_ELF_FLAGS (EF_RISCV_FLOAT_ABI | EF_RISCV_RVC)

/* Returns 0 if everything is ok, != 0 in case of error.  */
int
process_elf_file (const char *file_name, const char *lib, int *flag,
		  unsigned int *osversion, char **soname, void *file_contents,
		  size_t file_length)
{
  ElfW(Ehdr) *elf_header = (ElfW(Ehdr) *) file_contents;
  Elf32_Ehdr *elf32_header = (Elf32_Ehdr *) elf_header;
  int ret;
  long eflags;

  /* RISC-V libraries are always libc.so.6+.  */
  if (!ret)
    *flag = FLAG_ELF_LIBC6;

  if (elf_header->e_ident [EI_CLASS] == ELFCLASS32)
    {
      ret = process_elf32_file (file_name, lib, flag, osversion, soname,
				file_contents, file_length);
      eflags = elf32_header->e_flags;
    }
  else
    {
      ret = process_elf64_file (file_name, lib, flag, osversion, soname,
				file_contents, file_length);
      eflags = elf32_header->e_flags;
    }

  /* RISC-V linkers encode the floating point ABI as part of the ELF headers.  */
  switch (eflags & EF_RISCV_FLOAT_ABI)
    {
      case EF_RISCV_FLOAT_ABI_SOFT:
        *flags |= FLAG_RISCV_FLOAT_ABI_SOFT;
	break;
      case EF_RISCV_FLOAT_ABI_DOUBLE:
        *flags |= FLAG_RISCV_FLOAT_ABI_DOUBLE;
	break;
      case EF_RISCV_FLOAT_ABI_QUAD:
        return 1;
    }

  /* RISC-V Linux ABIs mandate the presence of the C extension.  */
  if (eflags & EF_RISCV_RVC)
    return 1;

  /* The remainder of the header bits are reserved, so just be on the safe side
     and don't support them at all.  */
  if (eflags & SUPPORTED_ELF_FLAGS)
    return 1;

  return ret;
}

#undef __ELF_NATIVE_CLASS
#undef process_elf_file
#define process_elf_file process_elf32_file
#define __ELF_NATIVE_CLASS 32
#include "elf/readelflib.c"

#undef __ELF_NATIVE_CLASS
#undef process_elf_file
#define process_elf_file process_elf64_file
#define __ELF_NATIVE_CLASS 64
#include "elf/readelflib.c"
