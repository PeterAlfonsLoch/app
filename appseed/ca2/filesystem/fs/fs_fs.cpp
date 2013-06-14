#include "framework.h"


namespace fs
{


   fs::fs(::ca2::application * papp) :
      ca2(papp),
      ::ca2::section(papp)
   {

   }


   fs::~fs()
   {

   }


   bool fs::initialize()
   {

      if(m_papp->is_system())
      {

/*       
         System.factory().creatable_small < main_view > ();
         System.factory().creatable_small < tree > ();
         System.factory().creatable_small < list > ();
*/

      }

      return true;

   }
 


} // namespace fs



