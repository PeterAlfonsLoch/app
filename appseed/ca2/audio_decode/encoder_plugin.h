#pragma once

namespace audio_decode
{

   class encoder_plugin_set;
   class CLASS_DECL_ca encoder_plugin :
      virtual public ::radix::object
   {
      friend class encoder_plugin_set;
   public:
      encoder_plugin(::ca::application * papp);

      void SetPluginId(int iId);
      bool LoadModule(const char *);
      audio_decode::encoder * NewEncoder();
      void DeleteEncoder(audio_decode::encoder * pdecoder);

      int GetPluginId();

   protected:
      int                  m_iId;
      HINSTANCE            m_hinstance;
      audio_decode::encoder *    (*m_lpfnNewEncoder)(::ca::application * papp);
      void    (*m_lpfnDeleteEncoder)(void * pdecoder);
   public:
      ~encoder_plugin(void);
   };


} // namespace audio_decode

