#include "framework.h"
#include "aura/node/ansios/ansios.h"
#include "linux.h"

/***
*int32_t _validdrive( unsigned drive ) -
*
*Purpose: returns non zero if drive is a valid drive number.
*
*Entry: drive = 0 => default drive, 1 => a:, 2 => b: ...
*
*Exit:  0 => drive does not exist.
*
*Exceptions:
*
*******************************************************************************/
/*
int32_t __cdecl _validdrive (
    unsigned drive
    )
{
        unsigned retcode;
        char drvstr[4];

        if ( drive == 0 )
            return 1;

        drvstr[0] = (char) ('A' + drive - 1);
        drvstr[1] = ':';
        drvstr[2] = '\\';
        drvstr[3] = '\0';

        if ( ((retcode = GetDriveType( drvstr )) == DRIVE_UNKNOWN) ||
             (retcode == DRIVE_NO_ROOT_DIR) )
            return 0;

        return 1;
}*/

/*WCHAR * __cdecl _wgetdcwd (
        int32_t drive,
        WCHAR *pnbuf,
        int32_t maxlen
        );

        */
/***
*_TSCHAR *_getcwd(pnbuf, maxlen) - get current working directory of default drive
*
*Purpose:
*       _getcwd gets the current working directory for the ::fontopus::user,
*       placing it in the buffer pointed to by pnbuf.  It returns
*       the length of the string put in the buffer.  If the length
*       of the string exceeds the length of the buffer, maxlen,
*       then NULL is returned.  If pnbuf = NULL, maxlen is ignored.
*       An entry point "_getdcwd()" is defined with takes the above
*       parameters, plus a drive number.  "_getcwd()" is implemented
*       as a call to "_getcwd()" with the default drive (0).
*
*       If pnbuf = NULL, maxlen is ignored, and a buffer is automatically
*       allocated using malloc() -- a pointer to which is returned by
*       _getcwd().
*
*       side effects: no global data is used or affected
*
*Entry:
*       _TSCHAR *pnbuf = pointer to a buffer maintained by the ::fontopus::user;
*       int32_t maxlen = length of the buffer pointed to by pnbuf;
*
*Exit:
*       Returns pointer to the buffer containing the c.w.d. name
*       (same as pnbuf if non-NULL; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/

/*WCHAR * __cdecl _wgetcwd (
        WCHAR *pnbuf,
        int32_t maxlen
        )
{
        WCHAR *retval;


        retval = _wgetdcwd(0, pnbuf, maxlen);

        return retval;
}*/


/***
*_TSCHAR *_getdcwd(drive, pnbuf, maxlen) - get c.w.d. for given drive
*
*Purpose:
*       _getdcwd gets the current working directory for the ::fontopus::user,
*       placing it in the buffer pointed to by pnbuf.  It returns
*       the length of the string put in the buffer.  If the length
*       of the string exceeds the length of the buffer, maxlen,
*       then NULL is returned.  If pnbuf = NULL, maxlen is ignored,
*       and a buffer is automatically allocated using malloc() --
*       a pointer to which is returned by _getdcwd().
*
*       side effects: no global data is used or affected
*
*Entry:
*       int32_t drive   - number of the drive being inquired about
*                     0 = default, 1 = 'a:', 2 = 'b:', etc.
*       _TSCHAR *pnbuf - pointer to a buffer maintained by the ::fontopus::user;
*       int32_t maxlen  - length of the buffer pointed to by pnbuf;
*
*Exit:
*       Returns pointer to the buffer containing the c.w.d. name
*       (same as pnbuf if non-NULL; otherwise, malloc is
*       used to allocate a buffer)
*
*Exceptions:
*
*******************************************************************************/


/*WCHAR * __cdecl _wgetdcwd (
        int32_t drive,
        WCHAR *pnbuf,
        int32_t maxlen
        )
{
        WCHAR *p;
        WCHAR dirbuf[_MAX_PATH];
        WCHAR drvstr[4];
        int32_t len;
        WCHAR *pname; /* only used as argument to GetFullPathName */

        /*
         * GetCurrentDirectory only works for the default drive in Win32
         */
  /*      if ( drive != 0 ) {
            /*
             * Not the default drive - make sure it's valid.
             */
    /*        if ( !_validdrive(drive) ) {
                _doserrno = ERROR_INVALID_DRIVE;
//                errno = EACCES;
                return NULL;
            }

            /*
             * get the current directory string on that drive and its length
             */
      /*      drvstr[0] = (char) ('A' - 1 + drive);
            drvstr[1] = ':';
            drvstr[2] = '.';
            drvstr[3] = '\0';
            len = shell::GetFullPathName( drvstr,
                                   sizeof(dirbuf) / sizeof(_TSCHAR),
                                   dirbuf,
                                   &pname );

        } else {

            /*
             * get the current directory string and its length
             */
/*            len = GetCurrentDirectory( sizeof(dirbuf) / sizeof(_TSCHAR),
                                       (LPTSTR)dirbuf );
        }

        /* API call failed, or buffer not large enough */
  /*      if ( len == 0 || ++len > sizeof(dirbuf)/sizeof(_TSCHAR) )
            return NULL;

        /*
         * Set up the buffer.
         */
    /*    if ( (p = pnbuf) == NULL ) {
            /*
             * allocate a buffer for the ::fontopus::user.
             */
      /*      if ( (p = (WCHAR *)malloc(__max(len, maxlen) * sizeof(WCHAR)))
                 == NULL )
            {
//                errno = ENOMEM;
                return NULL;
            }
        }
        else if ( len > maxlen ) {
            /*
             * Won't fit in the ::fontopus::user-supplied buffer!
             */
//            errno = ERANGE; /* Won't fit in ::fontopus::user buffer */
        /*    return NULL;
        }

        /*
         * Place the current directory string into the ::fontopus::user buffer
         */
/*
        return wcscpy(p, dirbuf);
}

/*#ifndef WPRFLAG

/***
*int32_t _validdrive( unsigned drive ) -
*
*Purpose: returns non zero if drive is a valid drive number.
*
*Entry: drive = 0 => default drive, 1 => a:, 2 => b: ...
*
*Exit:  0 => drive does not exist.
*
*Exceptions:
*
*******************************************************************************/

/*int32_t __cdecl _validdrive (
    unsigned drive
    )
{
        unsigned retcode;
        char drvstr[4];

        if ( drive == 0 )
            return 1;

        drvstr[0] = 'A' + drive - 1;
        drvstr[1] = ':';
        drvstr[2] = '\\';
        drvstr[3] = '\0';

        if ( ((retcode = GetDriveType( drvstr )) == DRIVE_UNKNOWN) ||
             (retcode == DRIVE_NO_ROOT_DIR) )
            return 0;

        return 1;
}*/

namespace linux
{


shell shell::theLinuxShell;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

shell::shell()
{

}

shell::~shell()
{

}

bool shell::Initialize()
{
   return true;
}


} // namespace linux
