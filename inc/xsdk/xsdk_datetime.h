#if !defined(__XSDK_DATETIME_H__)
#define __XSDK_DATETIME_H__

#if defined(OS_IS_WINDOWS)
  #include <windows.h>
#else
  #include <time.h>
  #include <sys/time.h>
  #include <limits.h>
#endif
#include "xsdk_define.h"

BGN_NAMESPACE_XSDK

#ifdef  __cplusplus
extern "C"
{
#endif

#define DT_YEAR                 0x0001
#define DT_MONTH                0x0002
#define DT_DAY                  0x0004
#define DT_HOUR                 0x0010
#define DT_MINUTE               0x0020
#define DT_SECOND               0x0040
#define DT_MILLISECOND          0x0080

#define DT_HOUR_24              DT_HOUR
#define DT_HOUR_12              DT_HOUR|0x0001
#define DT_AM_or_PM             0x0100


#if !defined(IS_LEAPYEAR)
#define IS_LEAPYEAR(year)       (((year) % 400) == 0 || (((year) % 4) == 0 && ((year) % 100) != 0))
#endif  // IS_LEAPYEAR


#if !defined(DAYS_OF_YEAR)
#define DAYS_OF_YEAR(year, month, day) \
( \
  ( \
    (month) ==  1 ?   0 : \
    (month) ==  2 ?  31 : \
    (month) ==  3 ?  59 : \
    (month) ==  4 ?  90 : \
    (month) ==  5 ? 120 : \
    (month) ==  6 ? 151 : \
    (month) ==  7 ? 181 : \
    (month) ==  8 ? 212 : \
    (month) ==  9 ? 243 : \
    (month) == 10 ? 273 : \
    (month) == 11 ? 304 : \
    (month) == 12 ? 334 : 0 \
  ) + ((month) > 2 && IS_LEAPYEAR(year) ? 1 : 0L) \
  + (day) \
)
#endif  // DAYS_OF_YEAR


#if !defined(DAYS_OF_MONTH)
#define DAYS_OF_MONTH(year, month) \
( \
  ((month) == 1 || (month) == 3 || (month) == 5 || (month) == 7 || (month) == 8 || (month) == 10 || (month) == 12) ? 31 : \
  ((month) == 4 || (month) == 6 || (month) == 9 || (month) == 11) ? 30 : \
  ((month) == 2 && (!IS_LEAPYEAR(year))) ? 28 : \
  ((month) == 2 && IS_LEAPYEAR(year)) ? 29 : 0 \
)
#endif  // DAYS_OF_MONTH


#if !defined(DAY_OF_WEEK)
#define DAY_OF_WEEK(year, month, day) \
( \
  ( \
    (day) \
    + ((year) - (14 - (month)) / 12) \
    + ((year) - (14 - (month)) / 12) / 4 \
    - ((year) - (14 - (month)) / 12) / 100 \
    + ((year) - (14 - (month)) / 12) / 400 \
    + (31 * ((month) + 12 * ((14 - (month)) / 12) - 2) / 12) \
  ) % 7 \
)
#endif  // DAY_OF_WEEK


#if !defined(DATETIME_IS_VALID)
#define DATETIME_IS_VALID(stDatetime) \
( \
  (stDatetime.wYear >= 0 && stDatetime.wYear <= 9999) \
  && (stDatetime.wMonth >= 1 && stDatetime.wMonth <= 12) \
  && (stDatetime.wDay >= 1 && stDatetime.wDay <= DAYS_OF_MONTH(stDatetime.wYear, stDatetime.wMonth)) \
  && (stDatetime.wHour >= 0 && stDatetime.wHour <= 23) \
  && (stDatetime.wMinute >= 0 && stDatetime.wMinute <= 59) \
  && (stDatetime.wSecond >= 0 && stDatetime.wSecond <= 59) \
  && (stDatetime.wMilliseconds >= 0 && stDatetime.wMilliseconds <= 999) \
)
#endif  // DATETIME_IS_VALID


#if !defined(TIME_INTERVAL)
#define TIME_INTERVAL(t1, t2) \
((t1.wHour <= t2.wHour)\
 ? ((t2.wHour * 3600 + t2.wMinute * 60 + t2.wSecond) - (t1.wHour * 3600 + t1.wMinute * 60 + t1.wSecond))\
 : (86400 - (t1.wHour * 3600 + t1.wMinute * 60 + t1.wSecond) + (t2.wHour * 3600 + t2.wMinute * 60 + t2.wSecond)))
#endif  // TIME_INTERVAL


#if !defined(MONTH_ENG_NAME)
#define MONTH_ENG_NAME(month) \
( \
  (month) ==  1 ? "Jan" : \
  (month) ==  2 ? "Feb" : \
  (month) ==  3 ? "Mar" : \
  (month) ==  4 ? "Apr" : \
  (month) ==  5 ? "May" : \
  (month) ==  6 ? "Jun" : \
  (month) ==  7 ? "Jul" : \
  (month) ==  8 ? "Aug" : \
  (month) ==  9 ? "Sep" : \
  (month) == 10 ? "Oct" : \
  (month) == 11 ? "Nov" : \
  (month) == 12 ? "Dcl" : "" \
)
#endif  // MONTH_ENG_NAME


#if !defined(MONTH_NUMERIC)
#define MONTH_NUMERIC(pszMonthEngName) \
( \
  stricmp(pszMonthEngName, "Jan") == 0 ?  1 : \
  stricmp(pszMonthEngName, "Feb") == 0 ?  2 : \
  stricmp(pszMonthEngName, "Mar") == 0 ?  3 : \
  stricmp(pszMonthEngName, "Apr") == 0 ?  4 : \
  stricmp(pszMonthEngName, "May") == 0 ?  5 : \
  stricmp(pszMonthEngName, "Jun") == 0 ?  6 : \
  stricmp(pszMonthEngName, "Jul") == 0 ?  7 : \
  stricmp(pszMonthEngName, "Aug") == 0 ?  8 : \
  stricmp(pszMonthEngName, "Sep") == 0 ?  9 : \
  stricmp(pszMonthEngName, "Oct") == 0 ? 10 : \
  stricmp(pszMonthEngName, "Nov") == 0 ? 11 : \
  stricmp(pszMonthEngName, "Dcl") == 0 ? 12 : 0 \
)
#endif  // MONTH_NUMERIC


//------------------------------------------------------------------------------
// 功能描述：
//     将给定格式的时间字符串析取出时间的各部分数值，并存入SYSTEMTIME结构中，
//     时间字符串格式说明字符定义如下：
//         YYYY    : 4位数字年
//         YY      : 2位数字年
//         MM      : 2位数字月，不足2位补零
//         MON     : 3位月份英文缩写
//         DD      : 2位数字日，不足2位补零
//         HH24    : 2位24小时制数字时，不足2位补零，时间范围：00:00:00-23:59:59
//         HH/HH12 : 2位12小时制数字时，不足2位补零，时间范围：12:00:00-11:59:59
//         AM      : 上午，AM范围[夜里12:00:00-中午11:59:59]
//         PM      : 下午，PM范围[中午12:00:00-夜里11:59:59]
//         MI      : 2位数字分钟，不足2位补零
//         SS      : 2位数字秒钟，不足2位补零
//         nnn     : 3位数字毫秒，不足3位补零
// 参数说明：
//     p_refstDatetime[out]
//         日期时间字符串析取后的数据输出存储结构
//     p_pszDatetime[in]
//         日期时间字符串
//     p_pszFormat[in]
//         日期时间字符串的格式描述，日期时间格式串示例，如：
//             "YYYY-MM-DD HH24:MI:SS.nnn"
//             "YYYY-MM-DD HH:MI:SS AM/PM"
// 返回说明：
//     返回true，函数执行成功
//     返回false，函数执行失败
bool StringToDatetime(
  SYSTEMTIME &p_refstDatetime,
  const char *p_pszDatetime,
  const char *p_pszFormat
);

//------------------------------------------------------------------------------
// 功能描述：
//     将存储于SYSTEMTIME结构中的时间数据，按给定的格式描述输出时间字符串
//     时间字符串格式说明字符定义同StringToDatetime函数中的描述。
// 参数说明：
//     p_pszDatetime[out]
//         输出数据的空间地址
//     p_iDatetimeSize[in]
//         p_pszDatetime的空间大小
//     p_pszFormat[in]
//         输出时间字符串的格式说明
//     p_refstDatetime[in]
//         存储时间数据的SYSTEMTIME结构
// 返回说明：
//     返回出参参数p_pszDatetime
char * DatetimeToString(
  char *p_pszDatetime,
  int p_iDatetimeSize,
  const char *p_pszFormat,
  const SYSTEMTIME &p_refstDatetime
);

//------------------------------------------------------------------------------
// 功能描述：
//     根据指定日期时间的部位进行加减运算
// 参数说明：
//     p_refstODatetime[out]
//         运算后的数据输出存储结构
//     p_usiDtPart[in]
//         指示进行运算的日期时间的部位
//             DT_YEAR         : 年
//             DT_MONTH        : 月
//             DT_DAY          : 日
//             DT_HOUR         : 时
//             DT_MINUTE       : 分
//             DT_SECOND       : 秒
//             DT_MILLISECONDS : 毫秒
//     p_llInterval[in]
//         加减运算变化量
//     p_refstIDatetime[in]
//         待运算的日期时间数据存储结构
// 返回说明：
//     返回true，函数执行成功
//     返回false，函数执行失败
bool DatetimeAdd(
  SYSTEMTIME &p_refstODatetime,
  unsigned short p_usiDtPart,
  long long p_llInterval,
  const SYSTEMTIME &p_refstIDatetime
);

//------------------------------------------------------------------------------
// 功能描述：
//     根据指定日期时间的部位计算两个日期时间的差值
// 参数说明：
//     p_refstTimestamp[out]
//         当前时间戳
// 返回说明：
//     计算结果。
//         如果计算失败，将返回LLONG_MAX(=0x7fffffffffffffff(9223372036854775807LL))
long long DatetimeDiff(
  const SYSTEMTIME &p_refstBgnDatetime,
  const SYSTEMTIME &p_refstEndDatetime,
  unsigned short p_usiDtPart = DT_DAY
);

//------------------------------------------------------------------------------
// 功能描述：
//     获取当前时间戳
// 参数说明：
//     p_refstBgnDatetime[in]
//         开始时间
// 返回说明：
//     返回true，函数执行成功
//     返回false，函数执行失败
int GetCurrentTimestamp(SYSTEMTIME &p_refstTimestamp);

//------------------------------------------------------------------------------
// 功能描述：
//     根据指定数值型时间值得到时间结构体
// 参数说明：
//     p_refstBgnDatetime[out]
//         输出时间结构体
//     p_llTimestamp[in]
//         数值形式时间
// 返回说明：
//     返回XSDK_OK，函数执行成功
//     返回XSDK_KO，函数执行失败
int Int64ToDatetime(SYSTEMTIME &p_refstTimestamp, __int64 p_llTimestamp);

//------------------------------------------------------------------------------
// 功能描述：
//     根据时间结构体得到数值型时间
// 参数说明：
//     p_llTimestamp[out]
//         int64形式的时间
//     p_refstBgnDatetime[in]
//         输出时间结构体
// 返回说明：
//     返回XSDK_OK，函数执行成功
//     返回XSDK_KO，函数执行失败
int DatetimeToInt64(__int64 &p_llTimestamp, const SYSTEMTIME &p_refstTimestamp);

#ifdef __cplusplus
}
#endif

END_NAMESPACE_XSDK

#endif  // __XSDK_DATETIME_H__
