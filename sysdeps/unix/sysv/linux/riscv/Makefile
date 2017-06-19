ifeq ($(subdir),elf)
ifeq ($(build-shared),yes)
# This is needed for DSO loading from static binaries.
sysdep-dl-routines += dl-static
endif
endif

ifeq ($(subdir),stdlib)
gen-as-const-headers += ucontext_i.sym
endif

abi-variants := ilp32 ilp32f ilp32d lp64 lp64f lp64d

ifeq (,$(filter $(default-abi),$(abi-variants)))
$(error Unknown ABI $(default-abi), must be one of $(abi-variants))
endif

abi-ilp32-options     := -D__SIZEOF_INT__=4
abi-ilp32-condition   := (__SIZEOF_INT__ == 4)
abi-ilp32-options     += -D__SIZEOF_LONG__=4
abi-ilp32-condition   += && (__SIZEOF_LONG__ == 4)
abi-ilp32-options     += -D__SIZEOF_POINTER__=4
abi-ilp32-condition   += && (__SIZEOF_POINTER__ == 4)
abi-ilp32-options     += -D__riscv_float_abi_soft
abi-ilp32-condition   += && (defined __riscv_float_abi_soft)
abi-ilp32-options     += -U__riscv_float_abi_single
abi-ilp32-condition   += && (!defined __riscv_float_abi_single)
abi-ilp32-options     += -U__riscv_float_abi_double
abi-ilp32-condition   += && (!defined __riscv_float_abi_double)

abi-ilp32f-options    := -D__SIZEOF_INT__=4
abi-ilp32f-condition  := (__SIZEOF_INT__ == 4)
abi-ilp32f-options    += -D__SIZEOF_LONG__=4
abi-ilp32f-condition  += && (__SIZEOF_LONG__ == 4)
abi-ilp32f-options    += -D__SIZEOF_POINTER__=4
abi-ilp32f-condition  += && (__SIZEOF_POINTER__ == 4)
abi-ilp32f-options    += -U__riscv_float_abi_soft
abi-ilp32f-condition  += && (!defined __riscv_float_abi_soft)
abi-ilp32f-options    += -D__riscv_float_abi_single
abi-ilp32f-condition  += && (defined __riscv_float_abi_single)
abi-ilp32f-options    += -U__riscv_float_abi_double
abi-ilp32f-condition  += && (!defined __riscv_float_abi_double)

abi-ilp32d-options    := -D__SIZEOF_INT__=4
abi-ilp32d-condition  := (__SIZEOF_INT__ == 4)
abi-ilp32d-options    += -D__SIZEOF_LONG__=4
abi-ilp32d-condition  += && (__SIZEOF_LONG__ == 4)
abi-ilp32d-options    += -D__SIZEOF_POINTER__=4
abi-ilp32d-condition  += && (__SIZEOF_POINTER__ == 4)
abi-ilp32d-options    += -U__riscv_float_abi_soft
abi-ilp32d-condition  += && (!defined __riscv_float_abi_soft)
abi-ilp32d-options    += -U__riscv_float_abi_single
abi-ilp32d-condition  += && (!defined __riscv_float_abi_single)
abi-ilp32d-options    += -D__riscv_float_abi_double
abi-ilp32d-condition  += && (defined __riscv_float_abi_double)

abi-lp64-options      := -D__SIZEOF_INT__=4
abi-lp64-condition    := (__SIZEOF_INT__ == 4)
abi-lp64-options      += -D__SIZEOF_LONG__=8
abi-lp64-condition    += && (__SIZEOF_LONG__ == 8)
abi-lp64-options      += -D__SIZEOF_POINTER__=8
abi-lp64-condition    += && (__SIZEOF_POINTER__ == 8)
abi-lp64-options      += -D__riscv_float_abi_soft
abi-lp64-condition    += && (defined __riscv_float_abi_soft)
abi-lp64-options      += -U__riscv_float_abi_single
abi-lp64-condition    += && (!defined __riscv_float_abi_single)
abi-lp64-options      += -U__riscv_float_abi_double
abi-lp64-condition    += && (!defined __riscv_float_abi_double)

abi-lp64f-options     := -D__SIZEOF_INT__=4
abi-lp64f-condition   := (__SIZEOF_INT__ == 4)
abi-lp64f-options     += -D__SIZEOF_LONG__=8
abi-lp64f-condition   += && (__SIZEOF_LONG__ == 8)
abi-lp64f-options     += -D__SIZEOF_POINTER__=8
abi-lp64f-condition   += && (__SIZEOF_POINTER__ == 8)
abi-lp64f-options     += -U__riscv_float_abi_soft
abi-lp64f-condition   += && (!defined __riscv_float_abi_soft)
abi-lp64f-options     += -D__riscv_float_abi_single
abi-lp64f-condition   += && (defined __riscv_float_abi_single)
abi-lp64f-options     += -U__riscv_float_abi_double
abi-lp64f-condition   += && (!defined __riscv_float_abi_double)

abi-lp64d-options     := -D__SIZEOF_INT__=4
abi-lp64d-condition   := (__SIZEOF_INT__ == 4)
abi-lp64d-options     += -D__SIZEOF_LONG__=8
abi-lp64d-condition   += && (__SIZEOF_LONG__ == 8)
abi-lp64d-options     += -D__SIZEOF_POINTER__=8
abi-lp64d-condition   += && (__SIZEOF_POINTER__ == 8)
abi-lp64d-options     += -U__riscv_float_abi_soft
abi-lp64d-condition   += && (!defined __riscv_float_abi_soft)
abi-lp64d-options     += -U__riscv_float_abi_single
abi-lp64d-condition   += && (!defined __riscv_float_abi_single)
abi-lp64d-options     += -D__riscv_float_abi_double
abi-lp64d-condition   += && (defined __riscv_float_abi_double)
