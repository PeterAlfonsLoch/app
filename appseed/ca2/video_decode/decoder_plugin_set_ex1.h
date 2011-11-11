#pragma once

namespace video_decode
{

   class CLASS_DECL_ca decoder_plugin_set_ex1 :
      protected decoder_plugin_set
   {
   public:
      decoder_plugin_set_ex1(::ca::application * papp);

      decoder * GetNewDecoder(const char * lpcszFileName, ex1::file * pfile = NULL);
      decoder * GetNewDecoder(const char * lpcszFileName, ex1::file * pfile, const char * pszModule);

   public:
      virtual ~decoder_plugin_set_ex1(void);
   };

} // namespace audio_decode