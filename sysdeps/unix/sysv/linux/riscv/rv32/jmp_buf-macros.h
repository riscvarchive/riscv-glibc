/*
 * Produced by this program
 *
 * #include <stdio.h>
 * #include <unistd.h>
 * #include <setjmp.h>
 * #include <stddef.h>
 * 
 * int main(int argc, char **argv)
 * {
 *     printf("#define JMP_BUF_SIZE %d\n", sizeof(jmp_buf));
 *     printf("#define JMP_BUF_ALIGN %d\n", __alignof__(jmp_buf));
 *     printf("#define SIGJMP_BUF_SIZE %d\n", sizeof(sigjmp_buf));
 *     printf("#define SIGJMP_BUF_ALIGN %d\n", __alignof__(sigjmp_buf));
 *     printf("#define MASK_WAS_SAVED_OFFSET %d\n", offsetof(struct __jmp_buf_tag, __mask_was_saved));
 *     printf("#define SAVED_MASK_OFFSET %d\n", offsetof(struct __jmp_buf_tag, __saved_mask));
 * }
 */

#define JMP_BUF_SIZE 288
#define JMP_BUF_ALIGN 8
#define SIGJMP_BUF_SIZE 288
#define SIGJMP_BUF_ALIGN 8
#define MASK_WAS_SAVED_OFFSET 152
#define SAVED_MASK_OFFSET 156
