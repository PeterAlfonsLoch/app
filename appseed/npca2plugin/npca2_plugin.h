#pragma once


class __rect64;

int spaboot_start(const char * pszVersion, const char * pszId);


namespace primitive
{
   class memory;
}


namespace ex1
{
   class file;
}


namespace npca2
{

   enum e_check
   {
      check_before_auth,
      check_before_start,
   };


   class host_interaction;
   class system;

   class plugin
   {
   public:

      HWND                          m_hwndMessage;
      host_interaction *            m_puiHost;
      BYTE *                        m_lpbMemory;
      int                           m_iMemory;
      bool                          m_bOnPaint;
      RECT                          m_rect;
      bool                          m_bInitialized;
      bool                          m_bCa2JustInstalled;
      const char *                  m_pszUrl;
      const char *                  m_pszHeaders;
      primitive::memory *           m_pmemory;
      ::ex1::file *                 m_pfile;
      bool                          m_bPreCheck;
      int                           m_iHealingSurface;
      DWORD                         m_last_redraw;

      system *                      m_psystem;
      int                           m_iEdge;
      bergedge::bergedge *          m_pbergedge;

      bool                          m_bAppStarted;

      HANDLE                        m_hEventReady;

      bool                          m_bApp;


      plugin();


      virtual bool open_url(const char * psz) = 0;
      virtual void redraw() = 0;
      virtual bool is_ok() = 0;
      virtual void post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam) = 0;
      virtual void get_window_rect(__rect64 * lprect) = 0;
      virtual HWND get_host_window() = 0;
      
      // ca2.dll-absence-(ca2.dll-delay-load)-safe
      virtual void get_window_rect(LPRECT lprect) = 0;

      virtual host_interaction * create_host_interaction() = 0;
      virtual bool hist(const char * pszUrl);
      virtual void run_start_install(const char * pszRun);


      virtual void start_ca2();


      virtual void finalize();

      virtual bool os_native_bergedge_start();

      int starter_start(const char * pszId);

      virtual void onBarePaint(HDC hdc, LPCRECT lprect);
      virtual void onCa2Paint(HDC hdcWindow, LPCRECT lprect);
      virtual void onPaint(HDC hdcWindow, LPCRECT lprect);

      virtual void on_prepare_memory();

      virtual int npca2_plugin_start_bergedge_cube();
      //virtual UINT start_bergedge_cube();

      //static UINT __cdecl ThreadProcStart(LPVOID lpv);


      virtual bool pre_check();

      virtual bool check(e_check echeck);

   };

   ATOM MyRegisterClass(HINSTANCE hInstance);

} // namespace npca2