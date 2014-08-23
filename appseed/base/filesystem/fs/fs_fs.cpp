#include "framework.h"


namespace fs
{


   fs::fs(::axis::application * papp) :
      element(papp),
      ::aura::departament(papp)
   {

   }


   fs::~fs()
   {

   }


   bool fs::initialize()
   {

      if(m_pauraapp->is_system())
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



