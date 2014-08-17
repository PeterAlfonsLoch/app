#include "framework.h"


#if defined(WINDOWS)

#include <mmsystem.h>

#define ID_MP3_SMALL_BELL			40000

void play_small_bell();

uint32_t g_dwPrepareSmallBell = 0;


void prepare_small_bell(bool bExistsOk)
{
   g_dwPrepareSmallBell = ::get_tick_count();
#ifdef METROWIN

   throw "todo";

#else
   if((bExistsOk && file_exists_dup(dir::element("stage\\small_bell.mp3")))
   || read_resource_as_file_dup(dir::element("stage\\small_bell.mp3"), ::GetModuleHandleA("app.install.exe"), ID_MP3_SMALL_BELL, "MP3")
   || read_resource_as_file_dup(dir::element("stage\\small_bell.mp3"), ::GetModuleHandleA("app.sentinel.exe"), ID_MP3_SMALL_BELL, "MP3")
   || read_resource_as_file_dup(dir::element("stage\\small_bell.mp3"), ::GetModuleHandleA(NULL), ID_MP3_SMALL_BELL, "MP3"))
   {
      if(mciSendString(("open \"" + dir::element("stage\\small_bell.mp3") + "\" type mpegvideo alias small_bell_mp3"), NULL, 0, NULL) == 0)
      {
         mciSendString("close small_bell_mp3", NULL, 0, NULL);
      }
   }

#endif
}

void defer_play_small_bell()
{
   if(::get_tick_count() - g_dwPrepareSmallBell > 10 * 1000)
   {
      play_small_bell();
   }
}

void play_small_bell()
{
#ifdef METROWIN

   throw "todo";

#else

   if(read_resource_as_file_dup(dir::element("stage\\small_bell.mp3"), ::GetModuleHandleA("app.install.exe"), ID_MP3_SMALL_BELL, "MP3")
   || read_resource_as_file_dup(dir::element("stage\\small_bell.mp3"), ::GetModuleHandleA("app.sentinel.exe"), ID_MP3_SMALL_BELL, "MP3")
   || read_resource_as_file_dup(dir::element("stage\\small_bell.mp3"), ::GetModuleHandleA(NULL), ID_MP3_SMALL_BELL, "MP3")
   || file_exists_dup(dir::element("stage\\small_bell.mp3")))
   {
      if(mciSendString(("open \"" + dir::element("stage\\small_bell.mp3") + "\" type mpegvideo alias small_bell_mp3"), NULL, 0, NULL) == 0)
      {
         mciSendString("play small_bell_mp3", NULL, 0, NULL);
         Sleep(4884);
         mciSendString("close small_bell_mp3", NULL, 0, NULL);
      }
   }
#endif

}


#else

CLASS_DECL_BASE void prepare_small_bell(bool bExistsOk)
{
   
}

CLASS_DECL_BASE void play_small_bell()
{
   
}

CLASS_DECL_BASE void defer_play_small_bell()
{
   
}



#endif
