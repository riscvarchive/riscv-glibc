ifeq ($(subdir),elf)
sysdep_routines	+= dl-vdso
ifeq ($(build-shared),yes)
# This is needed for DSO loading from static binaries.
sysdep-dl-routines += dl-static
endif
endif

ifeq ($(subdir),misc)
sysdep_headers += sys/cachectl.h
sysdep_routines += flush-icache
endif

ifeq ($(subdir),stdlib)
gen-as-const-headers += ucontext_i.sym
endif

abi-variants := ilp32 ilp32d lp64 lp64d

ifeq (,$(filter $(default-abi),$(abi-variants)))
$(error Unknown ABI $(default-abi), must be one of $(abi-variants))
endif

abi-ilp32-condition   := (__SIZEOF_INT__ == 4)
abi-ilp32-condition   += && (__SIZEOF_LONG__ == 4)
abi-ilp32-condition   += && (__SIZEOF_POINTER__ == 4)
abi-ilp32-condition   += && (defined __riscv_float_abi_soft)

abi-ilp32d-condition  := (__SIZEOF_INT__ == 4)
abi-ilp32d-condition  += && (__SIZEOF_LONG__ == 4)
abi-ilp32d-condition  += && (__SIZEOF_POINTER__ == 4)
abi-ilp32d-condition  += && (defined __riscv_float_abi_double)

abi-lp64-condition    := (__SIZEOF_INT__ == 4)
abi-lp64-condition    += && (__SIZEOF_LONG__ == 8)
abi-lp64-condition    += && (__SIZEOF_POINTER__ == 8)
abi-lp64-condition    += && (defined __riscv_float_abi_soft)

abi-lp64d-condition   := (__SIZEOF_INT__ == 4)
abi-lp64d-condition   += && (__SIZEOF_LONG__ == 8)
abi-lp64d-condition   += && (__SIZEOF_POINTER__ == 8)
abi-lp64d-condition   += && (defined __riscv_float_abi_double)
