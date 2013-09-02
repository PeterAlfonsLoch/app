#pragma once


class waitable;


DWORD WaitForMultipleObjectsEx(DWORD dwSize, waitable ** pwaitableptra, int_bool bWaitForAll, DWORD dwTimeout, int_bool bAlertable);

DWORD WaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, int_bool bWaitForAll, DWORD dwTimeout);

DWORD MsgWaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, int_bool bWaitForAll, DWORD dwTimeout, DWORD dwWakeMask);

DWORD MsgWaitForMultipleObjectsEx(DWORD dwSize, waitable ** pwaitableptra, DWORD dwTimeout, DWORD dwWakeMask, DWORD dwFlags);

DWORD WaitForSingleObject(waitable * pwaitable, DWORD dwMilliseconds);

DWORD WaitForSingleObjectEx(waitable * pwaitable, DWORD dwMilliseconds, int_bool bAlertable);


#define MWMO_WAITALL        0x0001
#define MWMO_ALERTABLE      0x0002
#define MWMO_INPUTAVAILABLE 0x0004
