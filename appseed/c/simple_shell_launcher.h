#pragma once


// created near revision 4405
// this type information can be used with the information that the class below is replacing Shell Execute calls from windows original implementations,
// to detect erronous adaptations of replacement


class CLASS_DECL_c simple_shell_launcher
{
public:


   HWND        m_hwnd;
   vsstring    m_vssOperation;
   vsstring    m_vssFile;
   vsstring    m_vssParameters;
   vsstring    m_vssDirectory;
   int         m_iShow;


#ifdef WINDOWS

   HINSTANCE   m_h;

#else

   bool        m_bOk;
   int         m_pid;

#endif


   simple_shell_launcher(HWND hwnd, const char * pszOperation, const char * pszFile, const char * pszParameters, const char * pszDirectory, int iShow);


   void execute();


};


