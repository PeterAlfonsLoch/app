#include "framework.h"

bool WINAPI LocalFileTimeToFileTime( const FILETIME *localft, LPFILETIME utcft );
bool WINAPI FileTimeToLocalFileTime( const FILETIME *utcft, LPFILETIME localft );
bool WINAPI FileTimeToSystemTime( const FILETIME *ft, LPSYSTEMTIME syst );
bool WINAPI SystemTimeToFileTime( const SYSTEMTIME *syst, LPFILETIME ft );



void WINAPI GetSystemTimeAsFileTime(LPFILETIME time); /* [out] Destination for the current utc time */
