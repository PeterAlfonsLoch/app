#pragma once

namespace audio_decode
{

class CLASS_DECL_ca decoder_plugin_set :
   public array_del_ptr < decoder_plugin, decoder_plugin & >
{
public:

   decoder_plugin_set(::ca::application * papp);

   decoder_plugin * FindPlugin(const char * lpcszTitle);

   decoder_plugin * LoadPlugin(const char * lpcszTitle);
   
public:
   virtual ~decoder_plugin_set(void);
};

} // namespace audio_decode