#pragma once

namespace gen
{

   class CLASS_DECL_ca command_line : public ::radix::object
   {
   public:

      //plain char* version on UNICODE for source-code backwards compatibility
      //virtual void ParseParam(const WCHAR* pszParam, BOOL bFlag, BOOL bLast);
      virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast);

      BOOL m_bShowSplash;
      BOOL m_bRunEmbedded;
      BOOL m_bRunAutomated;
      int   m_nCmdShow;
      enum { FileNew, FileOpen, FilePrint, FilePrintTo, FileDDE, AppUnregister, FileNothing = -1 } m_nShellCommand;

      // not valid for FileNew
      var         m_varFile;

      // valid only for FilePrintTo
      string      m_strPrinterName;
      string      m_strDriverName;
      string      m_strPortName;

      var         m_varQuery;

      command_line();
      ~command_line();

      void ParseParamFlag(const char* pszParam);
      //void ParseParamNotFlag(const CHAR* pszParam);
      void ParseParamNotFlag(const char* pszParam);
      void ParseLast(BOOL bLast);

      command_line & operator = (const command_line & info)
      {
         m_bShowSplash     = info.m_bShowSplash;
         m_bRunEmbedded    = info.m_bRunEmbedded;
         m_bRunAutomated   = info.m_bRunAutomated;
         m_varFile         = info.m_varFile;
         m_strPrinterName  = info.m_strPrinterName;
         m_strPortName     = info.m_strPortName;
         return *this;
      }


   };

} // namespace gen
