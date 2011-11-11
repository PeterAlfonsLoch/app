#include "StdAfx.h"

namespace audio_decode
{

   decoder_plugin_set_ex1::decoder_plugin_set_ex1(::ca::application * papp) :
      decoder_plugin_set(papp),
      ca(papp)
   {
   }

   decoder_plugin_set_ex1::~decoder_plugin_set_ex1(void)
   {
   }


   decoder * decoder_plugin_set_ex1::GetNewDecoder(const char * lpcszFileName, ex1::file * pfile, bool bSeekable, int iReadBlockSize)
   {
      stringa straTitle;
      System.dir().ls_pattern(System.dir().ca2module(), "audio_decode_*.dll", NULL, &straTitle);


      stringa straPreferred;
      straPreferred.add("audio_decode_libmpg123.dll");

      // preferences
      straTitle.preferred(straPreferred);

      for(int i = 0; i < straTitle.get_count(); i++)
      {
         decoder * pdecoder = GetNewDecoder(lpcszFileName, pfile, straTitle[i], bSeekable, iReadBlockSize);
         if(pdecoder != NULL)
            return pdecoder;
      }
      return NULL;
   }


   decoder * decoder_plugin_set_ex1::GetNewDecoder(const char * lpcszFileName, ex1::file * pfile, const char * pszModule, bool bSeekable, int iReadBlockSize)
   {
      if(lpcszFileName == NULL)
      {
         try
         {
            decoder_plugin * pplugin = LoadPlugin(pszModule);
            if(pplugin != NULL)
            {
               decoder * pdecoder = pplugin->NewDecoder();
               pdecoder->DecoderSetSeekable(bSeekable);
               if(iReadBlockSize > 0)
               {
                  pdecoder->DecoderSetReadBlockSize(iReadBlockSize);
               }
               if(pdecoder->DecoderInitialize(pfile))
               {
                  return pdecoder;
               }
            }
         }
         catch(...)
         {
         }
      }
      return NULL;
   }

} // namespace audio_decode
