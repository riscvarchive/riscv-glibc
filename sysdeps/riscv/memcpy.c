#include <string.h>
#include <stdint.h>

#define MEMCPY_LOOP_BODY(a, b, t) {	\
    t tt = *b;				\
    a++, b++;				\
    *(a - 1) = tt;			\
  }

void *__memcpy(void *aa, const void *bb, size_t n)
{
  uintptr_t msk = sizeof(long) - 1;
  char *a = (char *)aa, *end = a + n;
  const char *b = (const char *)bb;
  long *la, *lend;
  const long *lb;
  int same_alignment = ((uintptr_t)a & msk) == ((uintptr_t)b & msk);

  /* Handle small cases, and those without mutual alignment.  */
  if (__glibc_unlikely(!same_alignment || n < sizeof(long)))
    {
small:
      while (a < end)
	MEMCPY_LOOP_BODY(a, b, char);
      return aa;
    }

  /* Obtain alignment.  */
  if (__glibc_unlikely(((uintptr_t)a & msk) != 0))
    while ((uintptr_t)a & msk)
      MEMCPY_LOOP_BODY(a, b, char);

  la = (long *)a;
  lb = (const long *)b;
  lend = (long *)((uintptr_t)end & ~msk);

  /* Handle large, aligned cases.  */
  if (__glibc_unlikely(la < lend - 8))
    while (la < lend - 8)
      {
	long b0 = *lb++;
	long b1 = *lb++;
	long b2 = *lb++;
	long b3 = *lb++;
	long b4 = *lb++;
	long b5 = *lb++;
	long b6 = *lb++;
	long b7 = *lb++;
	long b8 = *lb++;
	*la++ = b0;
	*la++ = b1;
	*la++ = b2;
	*la++ = b3;
	*la++ = b4;
	*la++ = b5;
	*la++ = b6;
	*la++ = b7;
	*la++ = b8;
      }

  /* Handle aligned, small case.  */
  while (la < lend)
    MEMCPY_LOOP_BODY(la, lb, long);

  /* Handle misaligned remainder.  */
  a = (char *)la;
  b = (const char *)lb;
  if (__glibc_unlikely(a < end))
    goto small;

  return aa;
}
weak_alias (__memcpy, memcpy)
libc_hidden_builtin_def (memcpy)
