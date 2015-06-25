#pragma once


namespace tts
{


   class CLASS_DECL_AURA speaker:
      virtual public object
   {
   public:

      
      speaker(::aura::application * papp);

      virtual ~speaker();


      virtual bool speak(const string & strText);

      virtual bool stop();

      virtual bool is_speaking();


   };


} // namespace tts






