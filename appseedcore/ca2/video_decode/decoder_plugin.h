#pragma once

namespace video_decode
{

   class decoder;
   class decoder_plugin_set;

   class CLASS_DECL_ca decoder_plugin :
      virtual public ::radix::object
   {
      friend class decoder_plugin_set;
   protected:
      string                     m_strTitle;
      HINSTANCE                  m_hinstance;
      decoder *                  (* m_lpfnNewDecoder)(::ca::application * papp);
      void                       (* m_lpfnDeleteDecoder)(decoder * pdecoder);

   public:
      decoder_plugin(::ca::application * papp);
      ~decoder_plugin(void);

      bool Load(const char * pszTitle);
      decoder * NewDecoder();
      void DeleteDecoder(decoder * pdecoder);

      string GetPluginTitle();

   };


} // namespace video_decode

