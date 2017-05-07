#pragma once


namespace tts
{


   class CLASS_DECL_AURA speaker:
      virtual public object
   {
   public:


      sp(speaker)          m_pspeakerFallback;


      speaker(::aura::application * papp);

      virtual ~speaker();


      virtual bool speak(const string & strText);

      virtual bool speak(const string & strLang, const string & strText, bool bSynch = false);

      virtual bool stop(string strLang);

      virtual bool is_speaking(string strLang);


   };


} // namespace tts






