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
   HINSTANCE   m_hinstApp;       // out when SEE_MASK_NOCLOSEPROCESS is specified
   ULONG       m_fMask;          // in, SEE_MASK_XXX values
   void *      m_lpIDList;       // in, valid when SEE_MASK_IDLIST is specified, PCIDLIST_ABSOLUTE, for use with SEE_MASK_IDLIST & SEE_MASK_INVOKEIDLIST
   LPCSTR      m_vssClass;       // in, valid when SEE_MASK_CLASSNAME is specified
   HKEY        m_hkeyClass;      // in, valid when SEE_MASK_CLASSKEY is specified
   DWORD       m_dwHotKey;       // in, valid when SEE_MASK_HOTKEY is specified
   union                       
   {                           
      HANDLE   m_hIcon;          // not used
      HANDLE   n_hMonitor;
   };           
   HANDLE      m_hProcess;       // out, valid when SEE_MASK_NOCLOSEPROCESS specified

#else

   bool        m_bOk;
   int         m_dwResult;
   int         m_pid;

#endif

protected:


   int         m_iMode;


public:


   simple_shell_launcher();
   simple_shell_launcher(HWND hwnd, const char * pszOperation, const char * pszFile, const char * pszParameters, const char * pszDirectory, int iShow);


   void execute();


   bool succeeded();


};




