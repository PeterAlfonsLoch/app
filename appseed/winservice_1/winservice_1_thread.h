#pragma once


namespace winservice_1
{

   class CLASS_DECL_CA2_WINSERVICE_1 thread :
      public simple_thread
   {
   public:
      bool     m_bTimerOn;
      message_window      m_window;
      bool m_bEnsureApps;

      thread(::ca::application * papp);
      virtual ~thread();

      int run();

      string stage();

      bool win_hook();
      bool win_unhook();


      double get_winactionarea_radius(point pt);

      void ensure_apps();

      void LowLevelMouseMessage(int nCode, WPARAM wparam, LPARAM lparam);
      static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wparam, LPARAM lparam);
      static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam);
      bool LowLevelKeyboardMessage(int nCode, WPARAM wparam, LPARAM lparam);

      static BOOL CALLBACK GetAppsEnumWindowsProc(      
       HWND hwnd,
       LPARAM lParam);

      string m_strWinactionarea;
      id m_id;
      string m_strWinutil;
      HWND m_hwndWinactionarea;
      HWND m_hwndCommand;
      HWND m_hwndWinutil;
      HWND m_hwndWindesk;
      HWND m_hwndBergedge1;
      HWND m_hwndBergedge2;
      HWND m_hwndBergedge3;
      HWND m_hwndBergedge4;
      HWND m_hwndWhiteboard;
      point m_ptWinactionareaHotspot;
      bool  m_bInsideWinactionareaHotspot;

      void _001OnApp2000(gen::signal_object * pobj);

   };


} // namespace winservice_1

