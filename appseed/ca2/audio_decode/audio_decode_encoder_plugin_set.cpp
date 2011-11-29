#include "StdAfx.h"

namespace audio_decode
{

   encoder_plugin_set::encoder_plugin_set(::ca::application * papp) :
      ca(papp)
   {
   }

   encoder_plugin_set::~encoder_plugin_set(void)
   {
   }

   encoder_plugin * encoder_plugin_set::FindPlugin(int iId)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         if(this->element_at(i).GetPluginId() == iId)
            return &this->element_at(i);
      }
      return NULL;
   }

   encoder_plugin * encoder_plugin_set::LoadPlugin(int iId, const char * lpcszDll)
   {
      encoder_plugin * pplugin = FindPlugin(iId);
      if(pplugin != NULL)
         return pplugin;
      pplugin = new encoder_plugin(get_app());
      pplugin->SetPluginId(iId);
      pplugin->m_hinstance = ::LoadLibrary(lpcszDll);
      if(pplugin->m_hinstance == NULL)
      {
         TRACE("Fail to open decoder");
         return NULL;
      }
      pplugin->m_lpfnNewEncoder = (audio_decode::encoder *( * )(::ca::application * papp))::GetProcAddress(pplugin->m_hinstance, "NewEncoderInterface");
      if(pplugin->m_lpfnNewEncoder == NULL)
      {
         ::FreeLibrary(pplugin->m_hinstance);
         //str.Format("NewEncoderInterface function not found in %s", lpcszDll);
         throw "NewEncoderInterface function not found";
      }
      pplugin->m_lpfnDeleteEncoder = (void( * )(void *))::GetProcAddress(pplugin->m_hinstance, "DeleteEncoderInterface");
      if(pplugin->m_lpfnDeleteEncoder == NULL)
      {
         ::FreeLibrary(pplugin->m_hinstance);
         //str.Format("NewEncoderInterface function not found in %s", lpcszDll);
         throw "NewEncoderInterface function not found";
      }

      add(pplugin);
      return pplugin;
   }

} // namespace audio_decode
