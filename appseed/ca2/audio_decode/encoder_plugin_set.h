#pragma once


namespace audio_decode
{

   class CLASS_DECL_ca encoder_plugin_set :
      public array_del_ptr < encoder_plugin, encoder_plugin & >
   {
   public:

      encoder_plugin_set(::ca::application * papp);

      encoder_plugin * FindPlugin(int iId);

      encoder_plugin * LoadPlugin(int iId, const char * lpcszDll);

   public:
      virtual ~encoder_plugin_set(void);
   };

} // namespace audio_decode