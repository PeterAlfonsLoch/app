#include "framework.h"


namespace user
{


   window_map::window_map(sp(::axis::application) papp) :
      element(papp)
   {

   }

   window_map::~window_map()
   {

   }

   ::user::interaction_base * window_map::get(int_ptr iWindow)
   {
      ::user::interaction_base * pinterface;
      if(m_map.Lookup(iWindow, pinterface))
         return pinterface;
      else
         return NULL;
   }

   void window_map::set(int_ptr iWindow, const ::user::interaction_base *pinterface)
   {
      m_map.set_at(iWindow, (::user::interaction_base *) pinterface);
   }



}
