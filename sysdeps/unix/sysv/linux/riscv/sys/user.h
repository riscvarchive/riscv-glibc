/* x86 puts "struct user_regs_struct" in here, this is just a shim. */
#ifdef __USE_MISC
#include <asm/ptrace.h>
#endif
