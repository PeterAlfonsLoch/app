#include "StdAfx.h"

namespace audio_decode
{

decoder_plugin::decoder_plugin(::ca::application * papp)
: ca(papp)
{
   m_hinstance = NULL;
}

decoder_plugin::~decoder_plugin(void)
{
   if(m_hinstance != NULL)
   {
      ::FreeLibrary(m_hinstance);
   }
}


audio_decode::decoder * decoder_plugin::NewDecoder()
{
   audio_decode::decoder * pdecoder = m_lpfnNewDecoder(get_app());
   if(pdecoder == NULL)
   {
      ::FreeLibrary(m_hinstance);
      return NULL;
   }
   pdecoder->m_pplugin = this;
   return pdecoder;
}

void decoder_plugin::DeleteDecoder(audio_decode::decoder * pdecoder)
{
   m_lpfnDeleteDecoder(pdecoder);
}

bool decoder_plugin::Load(const char * pszTitle)
{
   SetDllDirectory(System.dir().ca2module());
   HINSTANCE hinstance = ::LoadLibrary(pszTitle);
   if(hinstance == NULL)
   {
      hinstance = ::LoadLibrary(System.dir().ca2module(pszTitle));
      if(hinstance == NULL)
      {
         DWORD dwLastError = GetLastError();
         TRACE("LoadLibrary failed to open library %s %d %s", pszTitle, dwLastError, win::error_message(dwLastError));
         return false;
      }
   }
   m_lpfnNewDecoder = (audio_decode::decoder *( * )(::ca::application * ))::GetProcAddress(hinstance, "NewDecoderInterface");
   if(m_lpfnNewDecoder == NULL)
   {
      ::FreeLibrary(hinstance);
      TRACE("NewDecoderInterface function not found in library %s", pszTitle);
      return false;
   }
   m_lpfnDeleteDecoder = (void( * )(audio_decode::decoder *))::GetProcAddress(hinstance, "DeleteDecoderInterface");
   if(m_lpfnDeleteDecoder == NULL)
   {
      ::FreeLibrary(hinstance);
      TRACE("DeleteDecoder function not found in library %s", pszTitle);
      return false;
   }

   m_hinstance = hinstance;
   m_strTitle = pszTitle;

   return true;

}

   inline string decoder_plugin::GetPluginTitle()
   {
      return m_strTitle;
   }


} // namespace audio_decode