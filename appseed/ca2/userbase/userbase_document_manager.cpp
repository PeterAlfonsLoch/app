#include "StdAfx.h"

AFX_STATIC_DATA const CHAR _vfxShellOpenFmt[] = "%s\\shell\\open\\%s";
AFX_STATIC_DATA const CHAR _vfxShellPrintFmt[] = "%s\\shell\\print\\%s";
AFX_STATIC_DATA const CHAR _vfxShellPrintToFmt[] = "%s\\shell\\printto\\%s";
AFX_STATIC_DATA const CHAR _vfxDefaultIconFmt[] = "%s\\DefaultIcon";
AFX_STATIC_DATA const CHAR _vfxShellNewFmt[] = "%s\\ShellNew";

#define DEFAULT_ICON_INDEX 0

AFX_STATIC_DATA const CHAR _vfxIconIndexFmt[] = ",%d";
AFX_STATIC_DATA const CHAR _vfxCommand[] = "command";
AFX_STATIC_DATA const CHAR _vfxOpenArg[] = " \"%1\"";
AFX_STATIC_DATA const CHAR _vfxPrintArg[] = " /p \"%1\"";
AFX_STATIC_DATA const CHAR _vfxPrintToArg[] = " /pt \"%1\" \"%2\" \"%3\" \"%4\"";
AFX_STATIC_DATA const CHAR _vfxDDEArg[] = " /dde";

AFX_STATIC_DATA const CHAR _vfxDDEExec[] = "ddeexec";
AFX_STATIC_DATA const CHAR _vfxDDEOpen[] = "[open(\"%1\")]";
AFX_STATIC_DATA const CHAR _vfxDDEPrint[] = "[print(\"%1\")]";
AFX_STATIC_DATA const CHAR _vfxDDEPrintTo[] = "[printto(\"%1\",\"%2\",\"%3\",\"%4\")]";

AFX_STATIC_DATA const CHAR _vfxShellNewValueName[] = "NullFile";
AFX_STATIC_DATA const CHAR _vfxShellNewValue[] = "";


#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? NULL : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)

/*BOOL vfxExtractSubString(string& rString, const wchar_t * lpszFullString,
   int iSubString, WCHAR chSep);*/
UINT AfxGetFileTitle(const wchar_t * lpszPathName, wchar_t * lpszTitle, UINT nMax);

AFX_STATIC BOOL AFXAPI
_AfxSetRegKey(const wchar_t * lpszKey, const wchar_t * lpszValue, const wchar_t * lpszValueName = NULL);

void AfxGetModuleShortFileName(HINSTANCE hInst, string& strShortName);



AFX_STATIC inline BOOL IsDirSep(WCHAR wch)
{
   return (wch == '\\' || wch == '/');
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AFX_STATIC_DATA const char _afxShellOpenFmt[] = "%s\\shell\\open\\%s";
AFX_STATIC_DATA const char _afxShellPrintFmt[] = "%s\\shell\\print\\%s";
AFX_STATIC_DATA const char _afxShellPrintToFmt[] = "%s\\shell\\printto\\%s";
AFX_STATIC_DATA const char _afxDefaultIconFmt[] = "%s\\DefaultIcon";
AFX_STATIC_DATA const char _afxShellNewFmt[] = "%s\\ShellNew";

#define DEFAULT_ICON_INDEX 0

AFX_STATIC_DATA const char _afxIconIndexFmt[] = ",%d";
AFX_STATIC_DATA const char _afxCommand[] = "command";
AFX_STATIC_DATA const char _afxOpenArg[] = _T(" \"%1\"");
AFX_STATIC_DATA const char _afxPrintArg[] = _T(" /p \"%1\"");
AFX_STATIC_DATA const char _afxPrintToArg[] = _T(" /pt \"%1\" \"%2\" \"%3\" \"%4\"");
AFX_STATIC_DATA const char _afxDDEArg[] = " /dde";

AFX_STATIC_DATA const char _afxDDEExec[] = "ddeexec";
AFX_STATIC_DATA const char _afxDDEOpen[] = _T("[open(\"%1\")]");
AFX_STATIC_DATA const char _afxDDEPrint[] = _T("[print(\"%1\")]");
AFX_STATIC_DATA const char _afxDDEPrintTo[] = _T("[printto(\"%1\",\"%2\",\"%3\",\"%4\")]");

AFX_STATIC_DATA const char _afxShellNewValueName[] = "NullFile";
AFX_STATIC_DATA const char _afxShellNewValue[] = "";


namespace userbase
{

   document_manager::document_manager(::ca::application * papp) :
      ca(papp)
   {
   }

#ifdef _DEBUG
   void document_manager::assert_valid() const
   {
      ::document_manager::assert_valid();
   }

   void document_manager::dump(dump_context & dumpcontext) const
   {
      ::document_manager::dump(dumpcontext);

   }
#endif

   document_manager::~document_manager()
   {
   }

   BOOL _AfxDeleteRegKey(const wchar_t * lpszKey)
   {
      // copy the string
      wchar_t * lpszKeyCopy = _wcsdup(lpszKey);
      wchar_t * lpszLast = lpszKeyCopy + lstrlenW(lpszKeyCopy);

      // work until the end of the string
      while (lpszLast != NULL)
      {
         *lpszLast = '\0';
         lpszLast = _wcsdec(lpszKeyCopy, lpszLast);

         // try to open that key
         HKEY hKey;
         if (::RegOpenKeyW(HKEY_CLASSES_ROOT, lpszKeyCopy, &hKey) != ERROR_SUCCESS)
            break;

         // enumerate the keys underneath
         WCHAR szScrap[_MAX_PATH+1];
         DWORD dwLen = _countof(szScrap);
         BOOL bItExists = FALSE;

         if (::RegEnumKeyW(hKey, 0, szScrap, dwLen) == ERROR_SUCCESS)
            bItExists = TRUE;
         ::RegCloseKey(hKey);

         // found one?  quit looping
         if (bItExists)
            break;

         // otherwise, delete and find the previous backwhack
         ::RegDeleteKeyW(HKEY_CLASSES_ROOT, lpszKeyCopy);
         lpszLast = wcsrchr(lpszKeyCopy, '\\');
      }

      // release the string and return
      free(lpszKeyCopy);
      return TRUE;
   }

   AFX_STATIC BOOL AFXAPI
   _AfxSetRegKey(const wchar_t * lpszKey, const wchar_t * lpszValue, const wchar_t * lpszValueName)
   {
      if (lpszValueName == NULL)
      {
         if (::RegSetValueW(HKEY_CLASSES_ROOT, lpszKey, REG_SZ,
              lpszValue, lstrlenW(lpszValue) * sizeof(char)) != ERROR_SUCCESS)
         {
//            TRACE1("Warning: registration database update failed for key '%s'.\n",
  //             lpszKey);
            return FALSE;
         }
         return TRUE;
      }
      else
      {
         HKEY hKey;

         if(::RegCreateKeyW(HKEY_CLASSES_ROOT, lpszKey, &hKey) == ERROR_SUCCESS)
         {
            LONG lResult = ::RegSetValueExW(hKey, lpszValueName, 0, REG_SZ,
               (CONST BYTE*)lpszValue, (lstrlenW(lpszValue) + 1) * sizeof(char));

            if(::RegCloseKey(hKey) == ERROR_SUCCESS && lResult == ERROR_SUCCESS)
               return TRUE;
         }
//         TRACE1("Warning: registration database update failed for key '%s'.\n", lpszKey);
         return FALSE;
      }
   }

} // namespace userbase


