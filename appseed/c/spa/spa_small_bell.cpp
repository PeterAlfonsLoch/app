#include "StdAfx.h"


#if defined(WINDOWS)

#define ID_MP3_SMALL_BELL			40000


DWORD g_dwPrepareSmallBell = 0;


void prepare_small_bell(bool bExistsOk)
{
   g_dwPrepareSmallBell = ::GetTickCount();
   if((bExistsOk && file_exists_dup(dir::ca2("stage\\small_bell.mp3")))
   || read_resource_as_file_dup(dir::ca2("stage\\small_bell.mp3"), ::GetModuleHandleA("app-install.exe"), ID_MP3_SMALL_BELL, "MP3")
   || read_resource_as_file_dup(dir::ca2("stage\\small_bell.mp3"), ::GetModuleHandleA("app-sentinel.exe"), ID_MP3_SMALL_BELL, "MP3")
   || read_resource_as_file_dup(dir::ca2("stage\\small_bell.mp3"), ::GetModuleHandleA(NULL), ID_MP3_SMALL_BELL, "MP3"))
   {
      if(mciSendString(("open \"" + dir::ca2("stage\\small_bell.mp3") + "\" type mpegvideo alias small_bell_mp3"), NULL, 0, NULL) == 0)
      {
         mciSendString("close small_bell_mp3", NULL, 0, NULL);
      }
   }
}

void defer_play_small_bell()
{
   if(::GetTickCount() - g_dwPrepareSmallBell > 10 * 1000)
   {
      play_small_bell();
   }
}

void play_small_bell()
{
   if(read_resource_as_file_dup(dir::ca2("stage\\small_bell.mp3"), ::GetModuleHandleA("app-install.exe"), ID_MP3_SMALL_BELL, "MP3")
   || read_resource_as_file_dup(dir::ca2("stage\\small_bell.mp3"), ::GetModuleHandleA("app-sentinel.exe"), ID_MP3_SMALL_BELL, "MP3")
   || read_resource_as_file_dup(dir::ca2("stage\\small_bell.mp3"), ::GetModuleHandleA(NULL), ID_MP3_SMALL_BELL, "MP3")
   || file_exists_dup(dir::ca2("stage\\small_bell.mp3")))
   {
      if(mciSendString(("open \"" + dir::ca2("stage\\small_bell.mp3") + "\" type mpegvideo alias small_bell_mp3"), NULL, 0, NULL) == 0)
      {
         mciSendString("play small_bell_mp3", NULL, 0, NULL);
         Sleep(4884);
         mciSendString("close small_bell_mp3", NULL, 0, NULL);
      }
   }
}


#else

CLASS_DECL_c void prepare_small_bell(bool bExistsOk)
{
   
}

CLASS_DECL_c void play_small_bell()
{
   
}

CLASS_DECL_c void defer_play_small_bell()
{
   
}



#endif
