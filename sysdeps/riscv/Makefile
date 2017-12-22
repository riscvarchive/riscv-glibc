ifneq ($(all-rtld-routines),)
# We can't have anything in ld.so call via the PLT because it won't have been
# resolved yet.
CFLAGS-.o += -mno-plt
endif

CFLAGS-closedir.c += -mno-plt
CFLAGS-exit.c += -mno-plt
CFLAGS-cxa_atexit.c += -mno-plt

ifeq ($(subdir),misc)
sysdep_headers += sys/asm.h
endif

ASFLAGS-.os += $(pic-ccflag)

ifeq ($(subdir),math)
CPPFLAGS += -I../soft-fp
endif
