// #include "framework.h"


namespace tts
{


   speaker::speaker(::aura::application * papp):
      object(papp)
   {

   }

   speaker::~speaker()
   {
   }


   bool speaker::speak(const string & strText)
   {

      return false;

   }


   bool speaker::stop()
   {
   
      return false;

   }

   
   bool speaker::is_speaking()
   {

      return false;

   }



} // namespace tts




