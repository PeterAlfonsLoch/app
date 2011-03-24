#pragma once

namespace audio_decode
{

   class CLASS_DECL_ca decoder_plugin_set_ex1 :
      public decoder_plugin_set
   {
   public:
      decoder_plugin_set_ex1(::ca::application * papp);

      decoder * GetNewDecoder(const char * lpcszFileName, ex1::file * pfile = NULL, bool bSeekable = true);
      decoder * GetNewDecoder(const char * lpcszFileName, ex1::file * pfile, const char * pszModule, bool bSeekable = true);

   public:
      virtual ~decoder_plugin_set_ex1(void);
   };

} // namespace audio_decode