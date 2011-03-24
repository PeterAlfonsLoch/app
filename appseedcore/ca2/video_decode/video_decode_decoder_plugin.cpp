#include "StdAfx.h"

namespace video_decode
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


   video_decode::decoder * decoder_plugin::NewDecoder()
   {
      video_decode::decoder * pdecoder = m_lpfnNewDecoder(get_app());
      if(pdecoder == NULL)
      {
         ::FreeLibrary(m_hinstance);
         return NULL;
      }
      return pdecoder;
   }

   void decoder_plugin::DeleteDecoder(video_decode::decoder * pdecoder)
   {
      m_lpfnDeleteDecoder(pdecoder);
   }

   bool decoder_plugin::Load(const char * pszTitle)
   {
      HINSTANCE hinstance = ::LoadLibrary(pszTitle);
      if(hinstance == NULL)
      {
         DWORD dwLastError = GetLastError();
         TRACE("LoadLibrary failed to open library %s %d %s", pszTitle, dwLastError, win::error_message(dwLastError));
         return false;
      }
      m_lpfnNewDecoder = (video_decode::decoder *( * )(::ca::application * ))::GetProcAddress(hinstance, "NewDecoderInterface");
      if(m_lpfnNewDecoder == NULL)
      {
         ::FreeLibrary(hinstance);
         TRACE("NewDecoderInterface function not found in library %s", pszTitle);
         return false;
      }
      m_lpfnDeleteDecoder = (void( * )(video_decode::decoder *))::GetProcAddress(hinstance, "DeleteDecoderInterface");
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

   string decoder_plugin::GetPluginTitle()
   {
      return m_strTitle;
   }


} // namespace video_decode