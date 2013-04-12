#include "framework.h"

static const char _vfxShellOpenFmt[] = "%s\\shell\\open\\%s";
static const char _vfxShellPrintFmt[] = "%s\\shell\\print\\%s";
static const char _vfxShellPrintToFmt[] = "%s\\shell\\printto\\%s";
static const char _vfxDefaultIconFmt[] = "%s\\DefaultIcon";
static const char _vfxShellNewFmt[] = "%s\\ShellNew";

#define DEFAULT_ICON_INDEX 0

static const char _vfxIconIndexFmt[] = ",%d";
static const char _vfxCommand[] = "command";
static const char _vfxOpenArg[] = " \"%1\"";
static const char _vfxPrintArg[] = " /p \"%1\"";
static const char _vfxPrintToArg[] = " /pt \"%1\" \"%2\" \"%3\" \"%4\"";
static const char _vfxDDEArg[] = " /dde";

static const char _vfxDDEExec[] = "ddeexec";
static const char _vfxDDEOpen[] = "[open(\"%1\")]";
static const char _vfxDDEPrint[] = "[print(\"%1\")]";
static const char _vfxDDEPrintTo[] = "[printto(\"%1\",\"%2\",\"%3\",\"%4\")]";

static const char _vfxShellNewValueName[] = "NullFile";
static const char _vfxShellNewValue[] = "";


#define _wcsdec(_cpc1, _cpc2) ((_cpc1)>=(_cpc2) ? ::null() : (_cpc2)-1)

#define _wcsinc(_pc)    ((_pc)+1)

/*bool vfxExtractSubString(string& rString, const wchar_t * lpszFullString,
   int32_t iSubString, WCHAR chSep);*/
UINT __get_file_title(const wchar_t * lpszPathName, wchar_t * lpszTitle, UINT nMax);

bool _set_reg_key(const wchar_t * lpszKey, const wchar_t * lpszValue, const wchar_t * lpszValueName = ::null());

void __get_module_short_file_name(HINSTANCE hInst, string& strShortName);



inline bool IsDirSep(wchar_t wch)
{
   return (wch == L'\\' || wch == L'/');
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

static const char gen_ShellOpenFmt[] = "%s\\shell\\open\\%s";
static const char gen_ShellPrintFmt[] = "%s\\shell\\print\\%s";
static const char gen_ShellPrintToFmt[] = "%s\\shell\\printto\\%s";
static const char gen_DefaultIconFmt[] = "%s\\DefaultIcon";
static const char gen_ShellNewFmt[] = "%s\\ShellNew";

#define DEFAULT_ICON_INDEX 0

static const char gen_IconIndexFmt[] = ",%d";
static const char gen_Command[] = "command";
//static const char gen_OpenArg[] = _T(" \"%1\"");
//static const char gen_PrintArg[] = _T(" /p \"%1\"");
//static const char gen_PrintToArg[] = _T(" /pt \"%1\" \"%2\" \"%3\" \"%4\"");
static const char gen_DDEArg[] = " /dde";

static const char gen_DDEExec[] = "ddeexec";
//static const char gen_DDEOpen[] = _T("[open(\"%1\")]");
//static const char gen_DDEPrint[] = _T("[print(\"%1\")]");
//static const char gen_DDEPrintTo[] = _T("[printto(\"%1\",\"%2\",\"%3\",\"%4\")]");

static const char gen_ShellNewValueName[] = "NullFile";
static const char gen_ShellNewValue[] = "";


namespace userbase
{

   document_manager::document_manager(sp(::ca::application) papp) :
      ca(papp)
   {
   }

#ifdef DEBUG
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
      while (lpszLast != ::null())
      {
         *lpszLast = '\0';
         lpszLast = _wcsdec(lpszKeyCopy, lpszLast);

         // try to open that key
         HKEY hKey;
         if (::RegOpenKeyW(HKEY_CLASSES_ROOT, lpszKeyCopy, &hKey) != ERROR_SUCCESS)
            break;

         // enumerate the keys underneath
         WCHAR szScrap[_MAX_PATH+1];
         uint32_t dwLen = _countof(szScrap);
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
      if (lpszValueName == ::null())
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


