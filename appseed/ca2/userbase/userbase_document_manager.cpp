#include "framework.h"

__STATIC_DATA const CHAR _vfxShellOpenFmt[] = "%s\\shell\\open\\%s";
__STATIC_DATA const CHAR _vfxShellPrintFmt[] = "%s\\shell\\print\\%s";
__STATIC_DATA const CHAR _vfxShellPrintToFmt[] = "%s\\shell\\printto\\%s";
__STATIC_DATA const CHAR _vfxDefaultIconFmt[] = "%s\\DefaultIcon";
__STATIC_DATA const CHAR _vfxShellNewFmt[] = "%s\\ShellNew";

#define DEFAULT_ICON_INDEX 0

__STATIC_DATA const CHAR _vfxIconIndexFmt[] = ",%d";
__STATIC_DATA const CHAR _vfxCommand[] = "command";
__STATIC_DATA const CHAR _vfxOpenArg[] = " \"%1\"";
__STATIC_DATA const CHAR _vfxPrintArg[] = " /p \"%1\"";
__STATIC_DATA const CHAR _vfxPrintToArg[] = " /pt \"%1\" \"%2\" \"%3\" \"%4\"";
__STATIC_DATA const CHAR _vfxDDEArg[] = " /dde";

__STATIC_DATA const CHAR _vfxDDEExec[] = "ddeexec";
__STATIC_DATA const CHAR _vfxDDEOpen[] = "[open(\"%1\")]";
__STATIC_DATA const CHAR _vfxDDEPrint[] = "[print(\"%1\")]";
__STATIC_DATA const CHAR _vfxDDEPrintTo[] = "[printto(\"%1\",\"%2\",\"%3\",\"%4\")]";

__STATIC_DATA const CHAR _vfxShellNewValueName[] = "NullFile";
__STATIC_DATA const CHAR _vfxShellNewValue[] = "";


#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? NULL : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)

/*bool vfxExtractSubString(string& rString, const wchar_t * lpszFullString,
   int iSubString, WCHAR chSep);*/
UINT __get_file_title(const wchar_t * lpszPathName, wchar_t * lpszTitle, UINT nMax);

__STATIC bool AFXAPI
__set_reg_key(const wchar_t * lpszKey, const wchar_t * lpszValue, const wchar_t * lpszValueName = NULL);

void __get_module_short_file_name(HINSTANCE hInst, string& strShortName);



__STATIC inline bool IsDirSep(WCHAR wch)
{
   return (wch == '\\' || wch == '/');
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

__STATIC_DATA const char gen_ShellOpenFmt[] = "%s\\shell\\open\\%s";
__STATIC_DATA const char gen_ShellPrintFmt[] = "%s\\shell\\print\\%s";
__STATIC_DATA const char gen_ShellPrintToFmt[] = "%s\\shell\\printto\\%s";
__STATIC_DATA const char gen_DefaultIconFmt[] = "%s\\DefaultIcon";
__STATIC_DATA const char gen_ShellNewFmt[] = "%s\\ShellNew";

#define DEFAULT_ICON_INDEX 0

__STATIC_DATA const char gen_IconIndexFmt[] = ",%d";
__STATIC_DATA const char gen_Command[] = "command";
__STATIC_DATA const char gen_OpenArg[] = _T(" \"%1\"");
__STATIC_DATA const char gen_PrintArg[] = _T(" /p \"%1\"");
__STATIC_DATA const char gen_PrintToArg[] = _T(" /pt \"%1\" \"%2\" \"%3\" \"%4\"");
__STATIC_DATA const char gen_DDEArg[] = " /dde";

__STATIC_DATA const char gen_DDEExec[] = "ddeexec";
__STATIC_DATA const char gen_DDEOpen[] = _T("[open(\"%1\")]");
__STATIC_DATA const char gen_DDEPrint[] = _T("[print(\"%1\")]");
__STATIC_DATA const char gen_DDEPrintTo[] = _T("[printto(\"%1\",\"%2\",\"%3\",\"%4\")]");

__STATIC_DATA const char gen_ShellNewValueName[] = "NullFile";
__STATIC_DATA const char gen_ShellNewValue[] = "";


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

/*   bool __delete_reg_key(const wchar_t * lpszKey)
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
         bool bItExists = FALSE;

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

   __STATIC bool AFXAPI
   __set_reg_key(const wchar_t * lpszKey, const wchar_t * lpszValue, const wchar_t * lpszValueName)
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
   */
} // namespace userbase


