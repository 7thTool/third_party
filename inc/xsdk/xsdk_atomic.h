#if !defined(__xsdk_atomic_h__)
#define __xsdk_atomic_h__

//#include "xsdk_define.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(OS_IS_WINDOWS)
  #include <Windows.h>
  #define xsdk_atomic_t                         LONG
  #define xsdk_AtomicAdd(mem, val)              InterlockedExchangeAdd(mem, val)
  #define xsdk_AtomicSet(mem, val)              InterlockedExchange(mem, val)
  #define xsdk_AtomicInc(mem)                   InterlockedIncrement(mem)
  #define xsdk_AtomicDec(mem)                   InterlockedDecrement(mem)
  #define xsdk_AtomicCas(mem, with, cmp)        InterlockedCompareExchange(mem, with, cmp)
  #define xsdk_AtomicRead(mem)                  (*mem)

  #define xsdk_Sleep(p_uiMilliseconds)          ::Sleep(p_uiMilliseconds)

#elif defined(OS_IS_LINUX)
  #include "unistd.h"
  #define xsdk_Sleep(p_uiMilliseconds)          ::usleep((p_uiMilliseconds)*1000)

  typedef volatile int xsdk_atomic_t;
  #define xsdk_AtomicAdd(mem, val)              (__sync_fetch_and_add(mem, (val)))
  #define xsdk_AtomicSet(mem, val)              (*mem = (val))
  #define xsdk_AtomicInc(mem)                   (__sync_add_and_fetch(mem, 1))
  #define xsdk_AtomicDec(mem)                   (__sync_sub_and_fetch(mem, 1))
  #define xsdk_AtomicCas(mem, with, cmp)        (__sync_val_compare_and_swap (mem, cmp, with)) 
  #define xsdk_AtomicRead(mem)                  (*mem)
#endif

#ifdef __cplusplus
}
#endif

#endif  // __xsdk_atomic_h__