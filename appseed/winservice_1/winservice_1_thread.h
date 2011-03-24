#pragma once
#include "win/kerr/servicebase.h"
#include "win/kerr/ManualResetEvent.h"



class CLASS_DECL_CA2_WINSERVICE_1 winservice_1_thread : public simple_thread
{
public:

   winservice_1_thread(::ca::application * papp);
   virtual ~winservice_1_thread();

   int Run();

   string stage();

   bool win_hook();
   bool win_unhook();

   bool m_bTimerOn;
   HWND m_hwnd;

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

   Kerr::ManualResetEvent m_stopped;
   bool m_stopping;


};


