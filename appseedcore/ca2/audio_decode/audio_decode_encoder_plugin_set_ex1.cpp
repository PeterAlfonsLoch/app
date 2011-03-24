#include "StdAfx.h"

namespace audio_decode
{

   encoder_plugin_set_ex1::encoder_plugin_set_ex1(::ca::application * papp) :
      encoder_plugin_set(papp),
      ca(papp)
   {
   }

   encoder_plugin_set_ex1::~encoder_plugin_set_ex1(void)
   {
   }


   encoder * encoder_plugin_set_ex1::GetNewEncoder(const char * lpcszFileName, ex1::filesp * pfile)
   {
      UNREFERENCED_PARAMETER(pfile);
      int len = strlen(lpcszFileName);
      audio_decode::encoder_plugin * pplugin = NULL;
      if(_strcmpi(&lpcszFileName[len - 4], ".wav") == 0)
      {
         pplugin = LoadPlugin(0, "audio_decode_wave.dll");
      }
      else if(_strcmpi(&lpcszFileName[len - 4], ".wma") == 0)
      {
         pplugin = LoadPlugin(1, "audio_decode_window_media.dll");
      }
      else if(_strcmpi(&lpcszFileName[len - 4], ".mp3") == 0)
      {
         pplugin = LoadPlugin(2, "auddec_mpglib.dll");
      }
      if(pplugin == NULL)
         return NULL;
      return pplugin->NewEncoder();
   }

} // namespace audio_decode