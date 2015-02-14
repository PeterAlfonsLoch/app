#pragma once


class object;


DWORD WaitForMultipleObjectsEx(DWORD dwSize, object ** pwaitableptra, int_bool bWaitForAll, DWORD dwTimeout, int_bool bAlertable);

DWORD WaitForMultipleObjects(DWORD dwSize, object ** pwaitableptra, int_bool bWaitForAll, DWORD dwTimeout);

DWORD MsgWaitForMultipleObjects(DWORD dwSize, object ** pwaitableptra, int_bool bWaitForAll, DWORD dwTimeout, DWORD dwWakeMask);

DWORD MsgWaitForMultipleObjectsEx(DWORD dwSize, object ** pwaitableptra, DWORD dwTimeout, DWORD dwWakeMask, DWORD dwFlags);

DWORD WaitForSingleObject(object * pwaitable, DWORD dwMilliseconds);

DWORD WaitForSingleObjectEx(object * pwaitable, DWORD dwMilliseconds, int_bool bAlertable);


#define MWMO_WAITALL        0x0001
#define MWMO_ALERTABLE      0x0002
#define MWMO_INPUTAVAILABLE 0x0004
