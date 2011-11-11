#include "StdAfx.h"

namespace video_decode
{

   decoder_plugin::decoder_plugin(::ca::application * papp)
   : ca(papp)
   {
   }

   decoder_plugin::~decoder_plugin(void)
   {
   }


   video_decode::decoder * decoder_plugin::NewDecoder()
   {
      video_decode::decoder * pdecoder = m_lpfnNewDecoder(get_app());
      if(pdecoder == NULL)
      {
         m_library.close();
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
      if(!m_library.open(pszTitle))
      {
         DWORD dwLastError = GetLastError();
         TRACE("LoadLibrary failed to open library %s %d %s", pszTitle, dwLastError, win::error_message(dwLastError));
         return false;
      }
      m_lpfnNewDecoder = m_library.get < video_decode::decoder *( * )(::ca::application * ) > ("video_decode_new_decoder");
      if(m_lpfnNewDecoder == NULL)
      {
         m_library.close();
         TRACE("NewDecoderInterface function not found in library %s", pszTitle);
         return false;
      }
      m_lpfnDeleteDecoder = m_library.get < void( * )(video_decode::decoder *) >("video_decode_delete_decoder");
      if(m_lpfnDeleteDecoder == NULL)
      {
         m_library.close();
         TRACE("DeleteDecoder function not found in library %s", pszTitle);
         return false;
      }

      m_strTitle = pszTitle;

      return true;

   }

   string decoder_plugin::GetPluginTitle()
   {
      return m_strTitle;
   }


} // namespace video_decode