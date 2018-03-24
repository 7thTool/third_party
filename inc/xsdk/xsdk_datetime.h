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
// ����������
//     ��������ʽ��ʱ���ַ�����ȡ��ʱ��ĸ�������ֵ��������SYSTEMTIME�ṹ�У�
//     ʱ���ַ�����ʽ˵���ַ��������£�
//         YYYY    : 4λ������
//         YY      : 2λ������
//         MM      : 2λ�����£�����2λ����
//         MON     : 3λ�·�Ӣ����д
//         DD      : 2λ�����գ�����2λ����
//         HH24    : 2λ24Сʱ������ʱ������2λ���㣬ʱ�䷶Χ��00:00:00-23:59:59
//         HH/HH12 : 2λ12Сʱ������ʱ������2λ���㣬ʱ�䷶Χ��12:00:00-11:59:59
//         AM      : ���磬AM��Χ[ҹ��12:00:00-����11:59:59]
//         PM      : ���磬PM��Χ[����12:00:00-ҹ��11:59:59]
//         MI      : 2λ���ַ��ӣ�����2λ����
//         SS      : 2λ�������ӣ�����2λ����
//         nnn     : 3λ���ֺ��룬����3λ����
// ����˵����
//     p_refstDatetime[out]
//         ����ʱ���ַ�����ȡ�����������洢�ṹ
//     p_pszDatetime[in]
//         ����ʱ���ַ���
//     p_pszFormat[in]
//         ����ʱ���ַ����ĸ�ʽ����������ʱ���ʽ��ʾ�����磺
//             "YYYY-MM-DD HH24:MI:SS.nnn"
//             "YYYY-MM-DD HH:MI:SS AM/PM"
// ����˵����
//     ����true������ִ�гɹ�
//     ����false������ִ��ʧ��
bool StringToDatetime(
  SYSTEMTIME &p_refstDatetime,
  const char *p_pszDatetime,
  const char *p_pszFormat
);

//------------------------------------------------------------------------------
// ����������
//     ���洢��SYSTEMTIME�ṹ�е�ʱ�����ݣ��������ĸ�ʽ�������ʱ���ַ���
//     ʱ���ַ�����ʽ˵���ַ�����ͬStringToDatetime�����е�������
// ����˵����
//     p_pszDatetime[out]
//         ������ݵĿռ��ַ
//     p_iDatetimeSize[in]
//         p_pszDatetime�Ŀռ��С
//     p_pszFormat[in]
//         ���ʱ���ַ����ĸ�ʽ˵��
//     p_refstDatetime[in]
//         �洢ʱ�����ݵ�SYSTEMTIME�ṹ
// ����˵����
//     ���س��β���p_pszDatetime
char * DatetimeToString(
  char *p_pszDatetime,
  int p_iDatetimeSize,
  const char *p_pszFormat,
  const SYSTEMTIME &p_refstDatetime
);

//------------------------------------------------------------------------------
// ����������
//     ����ָ������ʱ��Ĳ�λ���мӼ�����
// ����˵����
//     p_refstODatetime[out]
//         ��������������洢�ṹ
//     p_usiDtPart[in]
//         ָʾ�������������ʱ��Ĳ�λ
//             DT_YEAR         : ��
//             DT_MONTH        : ��
//             DT_DAY          : ��
//             DT_HOUR         : ʱ
//             DT_MINUTE       : ��
//             DT_SECOND       : ��
//             DT_MILLISECONDS : ����
//     p_llInterval[in]
//         �Ӽ�����仯��
//     p_refstIDatetime[in]
//         �����������ʱ�����ݴ洢�ṹ
// ����˵����
//     ����true������ִ�гɹ�
//     ����false������ִ��ʧ��
bool DatetimeAdd(
  SYSTEMTIME &p_refstODatetime,
  unsigned short p_usiDtPart,
  long long p_llInterval,
  const SYSTEMTIME &p_refstIDatetime
);

//------------------------------------------------------------------------------
// ����������
//     ����ָ������ʱ��Ĳ�λ������������ʱ��Ĳ�ֵ
// ����˵����
//     p_refstTimestamp[out]
//         ��ǰʱ���
// ����˵����
//     ��������
//         �������ʧ�ܣ�������LLONG_MAX(=0x7fffffffffffffff(9223372036854775807LL))
long long DatetimeDiff(
  const SYSTEMTIME &p_refstBgnDatetime,
  const SYSTEMTIME &p_refstEndDatetime,
  unsigned short p_usiDtPart = DT_DAY
);

//------------------------------------------------------------------------------
// ����������
//     ��ȡ��ǰʱ���
// ����˵����
//     p_refstBgnDatetime[in]
//         ��ʼʱ��
// ����˵����
//     ����true������ִ�гɹ�
//     ����false������ִ��ʧ��
int GetCurrentTimestamp(SYSTEMTIME &p_refstTimestamp);

//------------------------------------------------------------------------------
// ����������
//     ����ָ����ֵ��ʱ��ֵ�õ�ʱ��ṹ��
// ����˵����
//     p_refstBgnDatetime[out]
//         ���ʱ��ṹ��
//     p_llTimestamp[in]
//         ��ֵ��ʽʱ��
// ����˵����
//     ����XSDK_OK������ִ�гɹ�
//     ����XSDK_KO������ִ��ʧ��
int Int64ToDatetime(SYSTEMTIME &p_refstTimestamp, __int64 p_llTimestamp);

//------------------------------------------------------------------------------
// ����������
//     ����ʱ��ṹ��õ���ֵ��ʱ��
// ����˵����
//     p_llTimestamp[out]
//         int64��ʽ��ʱ��
//     p_refstBgnDatetime[in]
//         ���ʱ��ṹ��
// ����˵����
//     ����XSDK_OK������ִ�гɹ�
//     ����XSDK_KO������ִ��ʧ��
int DatetimeToInt64(__int64 &p_llTimestamp, const SYSTEMTIME &p_refstTimestamp);

#ifdef __cplusplus
}
#endif

END_NAMESPACE_XSDK

#endif  // __XSDK_DATETIME_H__
