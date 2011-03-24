#include "StdAfx.h"

wchar_t * AfxA2WHelper(wchar_t * lpw, const char * lpa, int nChars);

char * AfxW2AHelper(char * lpa, const wchar_t * lpw, int nChars);

#ifndef ATLA2WHELPER
#define ATLA2WHELPER AfxA2WHelper
#define ATLW2AHELPER AfxW2AHelper
#endif

/*#ifdef _CONVERSION_USES_THREAD_LOCALE
   #define W2A(lpw) (\
      ((_lpw = lpw) == NULL) ? NULL : (\
         _convert = (lstrlenW(_lpw)+1)*2,\
         ATLW2AHELPER((char *) alloca(_convert), _lpw, _convert, _acp)))
#else
   #define W2A(lpw) (\
      ((_lpw = lpw) == NULL) ? NULL : (\
         _convert = (lstrlenW(_lpw)+1)*2,\
         ATLW2AHELPER((char *) alloca(_convert), _lpw, _convert)))
#endif
*/
#define A2CW(lpa) ((const wchar_t *)A2W(lpa))
#define W2CA(lpw) ((const char *)W2A(lpw))


/*#ifdef _CONVERSION_USES_THREAD_LOCALE
   #ifndef _DEBUG
      #define USES_CONVERSION int _convert; _convert; UINT _acp = GetACP(); _acp; const wchar_t * _lpw; _lpw; const char * _lpa; _lpa
   #else
      #define USES_CONVERSION int _convert = 0; _convert; UINT _acp = GetACP(); _acp; const wchar_t * _lpw = NULL; _lpw; const char * _lpa = NULL; _lpa
   #endif
#else
   #ifndef _DEBUG
      #define USES_CONVERSION int _convert; _convert; UINT _acp = CP_ACP; _acp; const wchar_t * _lpw; _lpw; const char * _lpa; _lpa
   #else
      #define USES_CONVERSION int _convert = 0; _convert; UINT _acp = CP_ACP; _acp; const wchar_t * _lpw = NULL; _lpw; const char * _lpa = NULL; _lpa
   #endif
#endif

#ifdef _UNICODE
   #define T2A W2A
   #define A2T A2W
   inline wchar_t * T2W(LPTSTR lp) { return lp; }
   inline LPTSTR W2T(wchar_t * lp) { return lp; }
   #define T2CA W2CA
   #define A2CT A2CW
   inline const wchar_t * T2CW(const char * lp) { return lp; }
   inline const char * W2CT(const wchar_t * lp) { return lp; }
#else
   #define T2W A2W
   #define W2T W2A
   inline char * T2A(LPTSTR lp) { return lp; }
   inline LPTSTR A2T(char * lp) { return lp; }
   #define T2CW A2CW
   #define W2CT W2CA
   inline const char * T2CA(const char * lp) { return lp; }
   inline const char * A2CT(const char * lp) { return lp; }
#endif
*/
namespace gen
{

   /////////////////////////////////////////////////////////////////////////////
   // command_line implementation

   command_line::command_line()
   {
      m_bShowSplash = TRUE;
      m_bRunEmbedded = FALSE;
      m_bRunAutomated = FALSE;
      m_nShellCommand = FileNew;
   }

   command_line::~command_line()
   {
   }

   /*void command_line::ParseParam(const WCHAR* pszParam,BOOL bFlag,BOOL bLast)
   {
      if (bFlag)
      {
         USES_CONVERSION;
         ParseParamFlag(W2CA(pszParam));
      }
      else
         ParseParamNotFlag(pszParam);

      ParseLast(bLast);
   }*/

   void command_line::ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast)
   {
      if (bFlag)
         ParseParamFlag(pszParam);
      else
         ParseParamNotFlag(pszParam);

      ParseLast(bLast);
   }

   void command_line::ParseParamFlag(const char* pszParam)
   {
      // OLE command switches are case insensitive, while
      // shell command switches are case sensitive

      if (lstrcmpA(pszParam, "pt") == 0)
         m_nShellCommand = FilePrintTo;
      else if (lstrcmpA(pszParam, "p") == 0)
         m_nShellCommand = FilePrint;
      else if (lstrcmpiA(pszParam, "Unregister") == 0 ||
             lstrcmpiA(pszParam, "Unregserver") == 0)
         m_nShellCommand = AppUnregister;
      else if (lstrcmpA(pszParam, "dde") == 0)
      {
         m_nShellCommand = FileDDE;
      }
      else if (lstrcmpiA(pszParam, "Embedding") == 0)
      {
         m_bRunEmbedded = TRUE;
         m_bShowSplash = FALSE;
      }
      else if (lstrcmpiA(pszParam, "Automation") == 0)
      {
         m_bRunAutomated = TRUE;
         m_bShowSplash = FALSE;
      }
   }

   /*void command_line::ParseParamNotFlag(const WCHAR* pszParam)
   {
      if (m_strFileName.is_empty())
         m_strFileName = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_wstrPrinterName.is_empty())
         m_strPrinterName = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_wstrDriverName.is_empty())
         m_strDriverName = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_wstrPortName.is_empty())
         m_strPortName = pszParam;
   }*/

   void command_line::ParseParamNotFlag(const char* pszParam)
   {
      if (m_varFile.is_empty())
         m_varFile = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
         m_varFile = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
         m_varFile = pszParam;
      else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
         m_varFile = pszParam;
   }

   void command_line::ParseLast(BOOL bLast)
   {
      if (bLast)
      {
         if (m_nShellCommand == FileNew && !m_varFile.is_empty())
            m_nShellCommand = FileOpen;
         m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
      }
   }

} // namespace gen 
