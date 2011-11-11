#pragma once

namespace audio_decode
{

   class decoder_plugin_set;

   class CLASS_DECL_ca decoder_plugin :
      virtual public ::radix::object
   {
      friend class decoder_plugin_set;
   protected:
      string                     m_strTitle;
      HINSTANCE                  m_hinstance;
      audio_decode::decoder * (* m_lpfnNewDecoder)(::ca::application * papp);
      void                    (* m_lpfnDeleteDecoder)(audio_decode::decoder * pdecoder);

   public:
      decoder_plugin(::ca::application * papp);
      ~decoder_plugin(void);

      bool Load(const char * pszTitle);
      audio_decode::decoder * NewDecoder();
      void DeleteDecoder(audio_decode::decoder * pdecoder);

      string GetPluginTitle();

   };


} // namespace audio_decode

