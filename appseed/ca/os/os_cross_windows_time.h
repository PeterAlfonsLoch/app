#include "framework.h"

/*
 * RTL_SYSTEM_TIME and RTL_TIME_ZONE_INFORMATION are the same as
 * the SYSTEMTIME and TIME_ZONE_INFORMATION structures defined
 * in winbase.h, however we need to define them separately so
 * winternl.h doesn't depend on winbase.h.  They are used by
 * RtlQueryTimeZoneInformation and RtlSetTimeZoneInformation.
 * The names are guessed; if anybody knows the real names, let me know.
 */
typedef struct _RTL_SYSTEM_TIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} RTL_SYSTEM_TIME, *PRTL_SYSTEM_TIME;

typedef struct _RTL_TIME_ZONE_INFORMATION {
    LONG Bias;
    WCHAR StandardName[32];
    RTL_SYSTEM_TIME StandardDate;
    LONG StandardBias;
    WCHAR DaylightName[32];
    RTL_SYSTEM_TIME DaylightDate;
    LONG DaylightBias;
} RTL_TIME_ZONE_INFORMATION, *PRTL_TIME_ZONE_INFORMATION;


bool WINAPI LocalFileTimeToFileTime( const FILETIME *localft, LPFILETIME utcft );
bool WINAPI FileTimeToLocalFileTime( const FILETIME *utcft, LPFILETIME localft );
bool WINAPI FileTimeToSystemTime( const FILETIME *ft, LPSYSTEMTIME syst );
bool WINAPI SystemTimeToFileTime( const SYSTEMTIME *syst, LPFILETIME ft );

