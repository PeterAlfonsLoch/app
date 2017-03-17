#include "framework.h"


namespace user
{


   string interactive::fontopus_get_cred(::aura::application * papp, const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive, ::user::interactive * pinteractive)
   {

      if (bInteractive)
      {

         if (pinteractive != NULL)
         {

            return pinteractive->fontopus_get_cred(papp, strRequestUrl, rect, strUsername, strPassword, strToken, strTitle, true);

         }
         else
         {

            return papp->fontopus_get_cred(papp, strRequestUrl, rect, strUsername, strPassword, strToken, strTitle, true);

         }


      }
      else
      {

         return ::fontopus::get_cred(papp, strUsername, strPassword, strToken);

      }

   }


} // namespace user