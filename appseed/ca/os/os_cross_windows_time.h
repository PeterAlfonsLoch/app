
WINBOOL LocalFileTimeToFileTime(const FILETIME *localft, LPFILETIME utcft);
WINBOOL FileTimeToLocalFileTime(const FILETIME *utcft, LPFILETIME localft);
WINBOOL FileTimeToSystemTime(const FILETIME *ft, LPSYSTEMTIME syst);
WINBOOL SystemTimeToFileTime(const SYSTEMTIME *syst, LPFILETIME ft);



void GetSystemTimeAsFileTime(LPFILETIME time); /* [out] Destination for the current utc time */
