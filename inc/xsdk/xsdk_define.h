#if !defined(__xsdk_define_h__)
#define __xsdk_define_h__

#define BGN_NAMESPACE_XSDK      namespace xsdk {
#define END_NAMESPACE_XSDK      }
#define USE_NAMESPACE_XSDK      using namespace xsdk;

#define XSDK_OK                 0
#define XSDK_KO                 -1
#define XSDK_INVALID_PARAMTER   -99
#define XSDK_NO_DATA            100
#define XSDK_TIMEOUT            101
#define XSDK_EXISTS             102

// Base define.
#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64) || defined(_INC_WINDOWS)
  #if !defined(OS_IS_WINDOWS)
    #undef OS_IS_LINUX
    #define OS_IS_WINDOWS
  #endif
#else
  #undef OS_IS_WINDOWS
  #if !defined(OS_IS_LINUX)
    #define OS_IS_LINUX
  #endif
#endif

#if defined(OS_IS_WINDOWS)
  #define XSDK_DLL_EXPORT       __declspec(dllexport)
  #define XSDK_DLL_IMPORT       __declspec(dllimport)
#else
  #define XSDK_DLL_EXPORT
  #define XSDK_DLL_IMPORT
#endif  // defined(OS_IS_WINDOWS)

#if !defined(_W64)
  #if defined(OS_IS_WINDOWS) && _MSC_VER >= 1300
    #define _W64 __w64
  #else
    #define _W64
  #endif
#endif

#if !defined(NULL)
  #ifdef __cplusplus
    #define NULL                0
  #else
    #define NULL                ((void *)0)
  #endif
#endif

#if !defined(CONST)
  #define CONST                 const
#endif

#if !defined(FALSE)
  #define FALSE                 0
#endif

#if !defined(TRUE)
  #define TRUE                  1
#endif

#if !defined(INFINITE)
  #define INFINITE              0xFFFFFFFF
#endif

#if !defined(WAIT_TIMEOUT)
  #define WAIT_TIMEOUT          0x00000102
#endif

#if !defined(WAIT_OBJECT_0)
  #define WAIT_OBJECT_0         0x00000000
#endif

#if !defined(WAIT_ABANDONED)
  #define WAIT_ABANDONED        0x00000080
#endif

#if !defined(WAIT_FAILED)
  #define WAIT_FAILED           0xFFFFFFFF
#endif


#if defined(OS_IS_WINDOWS)
  //#define snprintf              _snprintf
  #define atoll                 _atoi64
  #define memicmp               _memicmp
  #define stricmp               _stricmp
  #define strnicmp              _strnicmp
#else
  #define stricmp               strcasecmp
  #define strnicmp              strncasecmp
#endif  // defined(OS_IS_WINDOWS)

// Base types.
#if !defined(OS_IS_WINDOWS) && !defined(__SQL)
  typedef signed int            BOOL;

  typedef unsigned char         BYTE, *PBYTE;
  typedef unsigned short        WORD, *PWORD;
  typedef unsigned int          DWORD, *PDWORD;

  typedef void                  VOID, *PVOID, *HANDLE;

  //typedef signed char           CHAR, *PCHAR;
  typedef char                  CHAR, *PCHAR;
  typedef unsigned char         UCHAR, *PUCHAR;
  typedef signed short          SHORT, *PSHORT;
  typedef unsigned short        USHORT, *PUSHORT;
  typedef signed int            INT, *PINT;
  typedef unsigned int          UINT, *PUINT;
  typedef signed long           LONG, *PLONG;
  typedef unsigned long         ULONG, *PULONG;
  typedef signed long long      LONGLONG, *PLONGLONG;
  typedef unsigned long long    ULONGLONG, *PULONGLONG;
  typedef float                 FLOAT, *PFLOAT;
  typedef double                DOUBLE, *PDOUBLE;

  typedef signed char           INT8, *PINT8;
  typedef unsigned char         UINT8, *PUINT8;
  typedef signed short          INT16, *PINT16;
  typedef unsigned short        UINT16, *PUINT16;
  typedef signed int            INT32, *PINT32;
  typedef unsigned int          UINT32, *PUINT32;
  #if defined(OS_IS_WINDOWS)
    typedef signed __int64      INT64, *PINT64;
    typedef unsigned __int64    UINT64, *PUINT64;
  #else
    typedef LONGLONG            INT64, *PINT64;
    typedef ULONGLONG           UINT64, *PUINT64;
  #endif

  #if (defined(OS_IS_LINUX) && !defined(__xlC__))
    typedef INT8                __int8;
    typedef INT16               __int16;
    typedef INT32               __int32;
    typedef INT64               __int64;
  #endif

  #if defined(_WIN64)
    typedef INT64               INT_PTR, *PINT_PTR;
    typedef UINT64              UINT_PTR, *PUINT_PTR;

    typedef INT64               LONG_PTR, *PLONG_PTR;
    typedef UINT64              ULONG_PTR, *PULONG_PTR;
  #else
    typedef _W64 INT            INT_PTR, *PINT_PTR;
    typedef _W64 UINT           UINT_PTR, *PUINT_PTR;

    typedef _W64 LONG           LONG_PTR, *PLONG_PTR;
    typedef _W64 ULONG          ULONG_PTR, *PULONG_PTR;
  #endif

  typedef WORD                  WCHAR, *PWCHAR;
  #if !defined(_TCHAR_DEFINED)
    #if defined(UNICODE)
      typedef WCHAR             TCHAR, *PTCHAR;
    #else
      //typedef CHAR              TCHAR, *PTCHAR;
      typedef char              TCHAR, *PTCHAR;
    #endif
  #endif  // !defined(_TCHAR_DEFINED)

  //typedef CHAR                  *LPSTR;
  typedef char                  *LPSTR;
  typedef CONST CHAR            *LPCSTR;
  typedef TCHAR                 *LPTSTR;
  typedef CONST TCHAR           *LPCTSTR;
#endif  // !defined(OS_IS_WINDOWS) && !defined(__SQL)

// Base defining functions.
#if !defined(xsdk_max)
  #define xsdk_max(a,b)              (((a) > (b)) ? (a) : (b))
#endif

#if !defined(xsdk_min)
  #define xsdk_min(a,b)              (((a) < (b)) ? (a) : (b))
#endif

#if !defined(MAKEWORD) && !defined(OS_IS_WINDOWS)
  #define MAKEWORD(a, b)        ((WORD)(((BYTE)((DWORD)(a) & 0xff)) | ((WORD)((BYTE)((DWORD)(b) & 0xff))) << 8))
#endif
#if !defined(MAKELONG) && !defined(OS_IS_WINDOWS)
  #define MAKELONG(a, b)        ((LONG)(((WORD)((DWORD)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD)(b) & 0xffff))) << 16))
#endif
#if !defined(LOWORD) && !defined(OS_IS_WINDOWS)
  #define LOWORD(l)             ((WORD)((DWORD)(l) & 0xffff))
#endif
#if !defined(HIWORD) && !defined(OS_IS_WINDOWS)
  #define HIWORD(l)             ((WORD)((DWORD)(l) >> 16))
#endif
#if !defined(LOBYTE) && !defined(OS_IS_WINDOWS)
  #define LOBYTE(w)             ((BYTE)((DWORD)(w) & 0xff))
#endif
#if !defined(HIBYTE) && !defined(OS_IS_WINDOWS)
  #define HIBYTE(w)             ((BYTE)((DWORD)(w) >> 8))
#endif

#if !defined(SNPRINTF_SYSAPI_ERRMSG)
  #if defined(OS_IS_WINDOWS)
    #define SNPRINTF_SYSAPI_ERRMSG(p_pszErrorMsg, p_iErrorMsgSize, p_pszHostFunc, p_pszCallFunc) \
    {\
      DWORD dwErrorCode = ::GetLastError();\
      LPSTR pszErrorMsg = NULL;\
      ::FormatMessage((FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS|FORMAT_MESSAGE_FROM_SYSTEM),\
                      NULL,\
                      dwErrorCode,\
                      LANG_NEUTRAL,\
                      (LPTSTR)&pszErrorMsg,\
                      0,\
                      NULL);\
      snprintf((p_pszErrorMsg), (p_iErrorMsgSize) - 1,\
               "[%s][%s][%ld - %s]",\
               (p_pszHostFunc),\
               (p_pszCallFunc),\
               dwErrorCode,\
               pszErrorMsg ? pszErrorMsg : "Unknow");\
      (p_pszErrorMsg)[(p_iErrorMsgSize) - 1] = 0x00;\
      ::LocalFree(pszErrorMsg);\
    }
  #else
    #define SNPRINTF_SYSAPI_ERRMSG(p_pszErrorMsg, p_iErrorMsgSize, p_pszHostFunc, p_pszCallFunc) \
    {\
      int iErrorCode = errno;\
      snprintf((p_pszErrorMsg), (p_iErrorMsgSize) - 1,\
               "[%s][%s][%d - %s]",\
               (p_pszHostFunc),\
               (p_pszCallFunc),\
               iErrorCode,\
               strerror(iErrorCode));\
      (p_pszErrorMsg)[(p_iErrorMsgSize) - 1] = 0x00;\
    }
  #endif  // defined(OS_IS_WINDOWS)
#endif  // !defined(SNPRINTF_SYSAPI_ERRMSG)

// Base structures.
#if !defined(OS_IS_WINDOWS) && !defined(__SQL)
  typedef struct _SYSTEMTIME
  {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
  }SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif  // !defined(OS_IS_WINDOWS) && !defined(__SQL)

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
  // union semun is defined by including <sys/sem.h>
#elif !defined(__XSDK_SEM_SEMUN_DEFINED__)
  #define __XSDK_SEM_SEMUN_DEFINED__
  // according to X/OPEN we have to define it ourselves
  union semun
  {
    int val;                  // value for SETVAL
    struct semid_ds *buf;     // buffer for IPC_STAT, IPC_SET
    unsigned short int *array;// array for GETALL, SETALL
    struct seminfo *__buf;    // buffer for IPC_INFO
  };
#endif

#if defined(OS_IS_WINDOWS) && !defined(snprintf)
#include <stdio.h>
#include <stdarg.h>
#define snprintf(str, size, format, ...)  (_snprintf(str, size, format, ## __VA_ARGS__) + ((str)[size -1] = 0x00))
#endif


// 为了提升字符串操作效率,重新定义strncpy(strncpy : strcpy的耗时是5: 1)
#if !defined(xsdk_strncpy)
#define xsdk_strncpy(p_pszDst, p_pszSrc, p_nSize) ((strlen(p_pszSrc) <= (p_nSize)) ? (strcpy((p_pszDst), (p_pszSrc))) : strncpy((p_pszDst), (p_pszSrc), (p_nSize)))
#endif


#endif  // __xsdk_define_h__