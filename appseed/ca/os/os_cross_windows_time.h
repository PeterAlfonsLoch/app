#pragma once


#ifdef METROWIN

struct timeval
{
   __int32    tv_sec;         /* seconds */
   __int32    tv_usec;        /* microseconds */
};

#endif

WINBOOL LocalFileTimeToFileTime(const FILETIME *localft, LPFILETIME utcft);
WINBOOL FileTimeToLocalFileTime(const FILETIME *utcft, LPFILETIME localft);
#ifndef METROWIN
WINBOOL FileTimeToSystemTime(const FILETIME *ft, LPSYSTEMTIME syst);
#endif
#ifndef METROWIN
WINBOOL SystemTimeToFileTime(const SYSTEMTIME *syst, LPFILETIME ft);
#endif


#ifndef METROWIN

void GetSystemTimeAsFileTime(LPFILETIME time); /* [out] Destination for the current utc time */

#endif

