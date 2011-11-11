#include "StdAfx.h"

namespace audio_decode
{

   encoder_plugin::encoder_plugin(::ca::application * papp) :
      ca(papp)
   {
      m_hinstance = NULL;
   }

   encoder_plugin::~encoder_plugin(void)
   {
      /*if(m_hinstance != NULL)
      {
         ::FreeLibrary(m_hinstance);
      }*/
   }

   void encoder_plugin::SetPluginId(int iId)
   {
      m_iId = iId;
   }

   audio_decode::encoder * encoder_plugin::NewEncoder()
   {
      audio_decode::encoder * pdecoder = m_lpfnNewEncoder(get_app());
      if(pdecoder == NULL)
      {
         ::FreeLibrary(m_hinstance);
         throw "Could not create new encoder";
         return false;
      }
      return pdecoder;
   }

   void encoder_plugin::DeleteEncoder(audio_decode::encoder * pdecoder)
   {
      m_lpfnDeleteEncoder(pdecoder);
   }

   int encoder_plugin::GetPluginId()
   {
      return m_iId;
   }


} // namespace audio_decode