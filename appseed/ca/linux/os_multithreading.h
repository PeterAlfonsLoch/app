#pragma once


class waitable;


DWORD WaitForMultipleObjectsEx(DWORD dwSize, waitable ** pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout, WINBOOL bAlertable);

DWORD WaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout);

DWORD MsgWaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout, DWORD dwWakeMask);

DWORD WaitForSingleObject(waitable * pwaitable, DWORD dwMilliseconds);
