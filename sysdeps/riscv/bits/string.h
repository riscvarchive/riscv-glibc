/* This file should provide inline versions of string functions.

   Surround GCC-specific parts with #ifdef __GNUC__, and use `__extern_inline'.

   This file should define __STRING_INLINES if functions are actually defined
   as inlines.  */

#ifndef _BITS_STRING_H
#define _BITS_STRING_H	1

#define _STRING_INLINE_unaligned   0

#if defined(__GNUC__) && !defined(__NO_STRING_INLINES)

#ifndef __STRING_INLINE
# ifndef __extern_inline
#  define __STRING_INLINE inline
# else
#  define __STRING_INLINE __extern_inline
# endif
#endif

__STRING_INLINE unsigned long __libc_detect_null(unsigned long w)
{
  unsigned long mask = 0x7f7f7f7f;
  if (sizeof(long) == 8)
    mask = ((mask << 16) << 16) | mask;
  return ~(((w & mask) + mask) | w | mask);
}

#define __aligned_to_const_size(k, p, n)				\
  (__extension__ (__builtin_constant_p (n)				\
		  && __alignof__(*(p)) >= (k)				\
		  && (n) % (k) == 0))

#define __memcpy_max_ops 8

#define __use_memcpy_c(t, d, s, n)					\
  (__aligned_to_const_size(sizeof (t), d, n)				\
   && __aligned_to_const_size(sizeof (t), s, n)				\
   && (n) / sizeof (t) <= __memcpy_max_ops)

#define __declare_memcpy_c(t)						\
  __STRING_INLINE void *__memcpy_c_##t (void *__restrict __d,		\
				     const void *__restrict __s,	\
				     size_t __n)			\
  {									\
    t *__td = (t *)__d;							\
    const t *__ts = (const t *)__s;					\
    switch ((__n) / sizeof (t))						\
      {									\
      case 8: *__td++ = *__ts++;					\
      case 7: *__td++ = *__ts++;					\
      case 6: *__td++ = *__ts++;					\
      case 5: *__td++ = *__ts++;					\
      case 4: *__td++ = *__ts++;					\
      case 3: *__td++ = *__ts++;					\
      case 2: *__td++ = *__ts++;					\
      case 1: *__td++ = *__ts++;					\
      case __memcpy_max_ops != 8: break;				\
      }									\
    return __d;								\
  }

#if defined(__OPTIMIZE__) && !defined(__OPTIMIZE_SIZE__)

#pragma GCC push_options
#pragma GCC ("funroll-loops")
__declare_memcpy_c(long)
__declare_memcpy_c(int)
#pragma GCC pop_options

#define _HAVE_STRING_ARCH_memcpy 1
#define memcpy(d, s, n)							\
  (__use_memcpy_c (long, d, s, n) ? __memcpy_c_long (d, s, n) :		\
   __use_memcpy_c (int, d, s, n) ? __memcpy_c_int (d, s, n) :		\
   memcpy(d, s, n))

#endif /* __OPTIMIZE__ && !__OPTIMIZE_SIZE__ */

#endif /* __GNUC__ */

#endif /* bits/string.h */
