ifeq ($(subdir),misc)
sysdep_headers += sys/asm.h
endif

# RISC-V's assembler also needs to know about PIC as it changes the definition
# of some assembler macros.
ASFLAGS-.os += $(pic-ccflag)

ifeq ($(subdir),math)
CPPFLAGS += -I../soft-fp
endif
