#undef new
#define min MIN
#define max MAX
#include <gdiplus.h>
#undef min
#undef max
#define new AURA_NEW




Gdiplus::GdiplusStartupInput *   g_pgdiplusStartupInput = NULL;
Gdiplus::GdiplusStartupOutput *  g_pgdiplusStartupOutput = NULL;
DWORD_PTR                        g_gdiplusToken = NULL;
DWORD_PTR                        g_gdiplusHookToken = NULL;



bool __node_axis_pre_init()
{


   g_pgdiplusStartupInput = new Gdiplus::GdiplusStartupInput();
   g_pgdiplusStartupOutput = new Gdiplus::GdiplusStartupOutput();
   g_gdiplusToken = NULL;
   g_gdiplusHookToken = NULL;

   g_pgdiplusStartupInput->SuppressBackgroundThread = TRUE;

   Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken, g_pgdiplusStartupInput, g_pgdiplusStartupOutput);

   if (statusStartup != Gdiplus::Ok)
   {

      simple_message_box(NULL, "Gdiplus Failed to Startup. ca cannot continue.", "Gdiplus Failure", MB_ICONERROR);

      return 0;

   }




   statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);


   if (statusStartup != Gdiplus::Ok)
   {

      simple_message_box(NULL, "Gdiplus Failed to Hook. ca cannot continue.", "Gdiplus Failure", MB_ICONERROR);

      return 0;

   }

   return true;

}


bool __node_axis_pos_init()
{

   return true;

}


bool __node_axis_pre_term()
{

   return true;

}


bool __node_axis_pos_term()
{

   g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);


   ::Gdiplus::GdiplusShutdown(g_gdiplusToken);


   ::aura::del(g_pgdiplusStartupInput);
   ::aura::del(g_pgdiplusStartupOutput);

   return true;

}







CLASS_DECL_AXIS HMONITOR GetUiMonitorHandle(HWND hwnd)
{

   return MonitorFromWindow(hwnd,MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_AXIS HMONITOR GetPrimaryMonitorHandle()
{

   const POINT ptZero ={0,0};

   return MonitorFromPoint(ptZero,MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_AXIS bool GetPrimaryMonitorRect(LPRECT lprect)
{

   MONITORINFO mi;

   ZERO(mi);

   mi.cbSize = sizeof(MONITORINFO);

   if(GetMonitorInfo(GetPrimaryMonitorHandle(),&mi))
   {

      *lprect = mi.rcMonitor;

   }
   else
   {

      if(!::GetWindowRect(::GetDesktopWindow(),lprect))
      {

         return false;

      }

   }

   return true;

}

