#ifndef ASSERT_H
#define ASSERT_H
#ifdef DEV_BUILD
#define assert(expression) \
  if(!(expression)) {      \
    *(int *)0 = 0;         \
  }
#else
#define assert(expression)
#endif
#endif // ASSERT_H