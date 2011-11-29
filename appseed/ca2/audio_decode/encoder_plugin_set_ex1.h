#pragma once

namespace audio_decode
{

   class CLASS_DECL_ca encoder_plugin_set_ex1 :
      protected encoder_plugin_set
   {
   public:
      encoder_plugin_set_ex1(::ca::application * papp);

      encoder * GetNewEncoder(const char * lpcszFileName, ex1::filesp * pfile = NULL);

   public:
      virtual ~encoder_plugin_set_ex1(void);
   };

} // namespace audio_decode