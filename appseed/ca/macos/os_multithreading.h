#pragma once


class waitable;


DWORD WaitForMultipleObjectsEx(DWORD dwSize, waitable ** pwaitableptra, bool bWaitForAll, DWORD dwTimeout, bool bAlertable);

DWORD WaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, bool bWaitForAll, DWORD dwTimeout);

DWORD MsgWaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, bool bWaitForAll, DWORD dwTimeout, DWORD dwWakeMask);

DWORD WaitForSingleObject(waitable * pwaitable, DWORD dwMilliseconds);
