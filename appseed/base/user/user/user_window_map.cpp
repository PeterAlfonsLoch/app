#include "framework.h"


namespace user
{


   window_map::window_map(sp(::base::application) papp) :
      element(papp)
   {

   }

   window_map::~window_map()
   {

   }

   ::user::window_interface * window_map::get(int_ptr iWindow)
   {
      ::user::window_interface * pinterface;
      if(m_map.Lookup(iWindow, pinterface))
         return pinterface;
      else
         return NULL;
   }

   void window_map::set(int_ptr iWindow, const ::user::window_interface *pinterface)
   {
      m_map.set_at(iWindow, (::user::window_interface *) pinterface);
   }



}
