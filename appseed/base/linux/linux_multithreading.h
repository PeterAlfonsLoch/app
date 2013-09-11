#pragma once


class waitable;


DWORD WaitForMultipleObjectsEx(DWORD dwSize, waitable ** pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout, WINBOOL bAlertable);

DWORD WaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout);

DWORD MsgWaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout, DWORD dwWakeMask);

DWORD MsgWaitForMultipleObjectsEx(DWORD dwSize, waitable ** pwaitableptra, DWORD dwTimeout, DWORD dwWakeMask, DWORD dwFlags);

DWORD WaitForSingleObject(waitable * pwaitable, DWORD dwMilliseconds);

DWORD WaitForSingleObjectEx(waitable * pwaitable, DWORD dwMilliseconds, WINBOOL bAlertable);


/*
#define STATUS_WAIT_0            ((DWORD   ) 0x00000000L)
#define STATUS_ABANDONED_WAIT_0  ((DWORD   ) 0x00000080L)
#define STATUS_USER_APC          ((DWORD   ) 0x000000C0L)
#define STATUS_TIMEOUT           ((DWORD   ) 0x00000102L)
*/

#define WAIT_FAILED              ((DWORD   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((DWORD   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)

#define WAIT_IO_COMPLETION                   STATUS_USER_APC

// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64




union semun
{

   int32_t val;
   struct semid_ds * buf;
   USHORT * array;

};


#define MWMO_WAITALL        0x0001
#define MWMO_ALERTABLE      0x0002
#define MWMO_INPUTAVAILABLE 0x0004
