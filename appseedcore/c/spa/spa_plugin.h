#pragma once



int spaboot_start(const char * pszVersion, const char * pszId);



   class host;

namespace spa
{

   enum e_check
   {
      check_before_auth,
      check_before_start,
   };


   class CLASS_DECL_____ plugin :
      virtual public ::hotplugin::plugin
   {
   public:

      canvas      m_canvas;



      plugin();
      virtual ~plugin();



      virtual bool hist(const char * pszUrl);
      virtual void run_start_install(const char * pszRun);


      virtual void start_ca2();


      //int starter_start(const char * pszId);

      virtual bool initialize();

      //virtual void on_bare_paint(HDC hdc, LPCRECT lprect);
      virtual void on_paint(HDC hdcWindow, LPCRECT lprect);

      virtual void on_prepare_memory();

#ifdef WINDOWS
      virtual UINT_PTR message_handler(UINT_PTR uiMessage, WPARAM wparam, LPARAM lparam);
#else
      virtual int message_handler(XEvent * pevent);
#endif

      virtual void on_paint_progress(HDC hdc, LPCRECT lprect);

      virtual double extract_spa_progress_rate();

      virtual void deferred_prodevian_redraw();

   };

#ifdef WINDOWS
   ATOM MyRegisterClass(HINSTANCE hInstance);
#endif

} // namespace spa
