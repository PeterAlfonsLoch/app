// #include "framework.h"


namespace tts
{


   speaker::speaker(::ace::application * papp):
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

   bool speaker::speak(const string & strLang, const string & strText, bool bSynch)
   {

      return false;

   }

   bool speaker::stop(string strLang)
   {
   
      return false;

   }

   
   bool speaker::is_speaking(string strLang)
   {

      return false;

   }



} // namespace tts




