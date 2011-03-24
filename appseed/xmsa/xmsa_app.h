#pragma once


class __declspec(dllexport) xmsa_app :
   public Ex2Application
{
public:
//	DECLARE_DYNAMIC(xmsa_app)
   xmsa_app(void);
   virtual ~xmsa_app(void);

   bool InitInstance();
   int ExitInstance();
   int Run();


   int m_iExit;

   Ex1FactoryImpl * Ex1AppGetFactoryImpl();


   void CreateChildProcess();
   void WriteToPipe(void);
   void ReadFromPipe(void);
   void ErrorExit(PTSTR lpszFunction);

   HANDLE m_hChildStd_IN_Rd;
   HANDLE m_hChildStd_IN_Wr;
   HANDLE m_hChildStd_OUT_Rd;
   HANDLE m_hChildStd_OUT_Wr;

   WCHAR *              m_pszCmdLine;
   int                  m_argc;
   WCHAR **             m_argv;
   WCHAR *              m_pwszExeName;


   CStdioFile m_file;
   string m_strRet;
   

};
