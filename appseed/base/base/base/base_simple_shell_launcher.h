#pragma once


#ifndef METROWIN


// created near revision 4405
// this type information can be used with the information that the class below is replacing Shell Execute calls from windows original implementations,
// to detect erronous adaptations of replacement


class CLASS_DECL_BASE simple_shell_launcher
{
public:


   oswindow        m_oswindow;
   string    m_vssOperation;
   string    m_vssFile;
   string    m_vssParameters;
   string    m_vssDirectory;
   int32_t         m_iShow;

#ifdef WINDOWS

   HINSTANCE   m_h;
   HINSTANCE   m_hinstApp;       // out when SEE_MASK_NOCLOSEPROCESS is specified
   ULONG       m_fMask;          // in, SEE_MASK_XXX values
   void *      m_lpIDList;       // in, valid when SEE_MASK_IDLIST is specified, PCIDLIST_ABSOLUTE, for use with SEE_MASK_IDLIST & SEE_MASK_INVOKEIDLIST
   LPCSTR      m_vssClass;       // in, valid when SEE_MASK_CLASSNAME is specified
   HKEY        m_hkeyClass;      // in, valid when SEE_MASK_CLASSKEY is specified
   uint32_t       m_dwHotKey;       // in, valid when SEE_MASK_HOTKEY is specified
   union                       
   {                           
      HANDLE   m_hIcon;          // not used
      HANDLE   n_hMonitor;
   };           
   HANDLE      m_hProcess;       // out, valid when SEE_MASK_NOCLOSEPROCESS specified

#else

   bool        m_bOk;
   int32_t         m_dwResult;
   int32_t         m_pid;

#endif

protected:


   int32_t         m_iMode;


public:


   simple_shell_launcher();
   simple_shell_launcher(oswindow oswindow, const char * pszOperation, const char * pszFile, const char * pszParameters, const char * pszDirectory, int32_t iShow);


   void execute();


   bool succeeded();


};




#endif









