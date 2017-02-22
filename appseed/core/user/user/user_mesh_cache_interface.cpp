#include "framework.h"


namespace user
{


   mesh_cache_interface::mesh_cache_interface(::aura::application * papp) :
      ::object(papp)
   {

      m_pmutex = new mutex(papp);

   }


   mesh_cache_interface::~mesh_cache_interface()
   {

   }


   void mesh_cache_interface::_001GetGroupText(::user::mesh_item * pitem)
   {


      pitem->m_bOk = false;


   }


} // namespace user