#include "StdAfx.h"


namespace user
{

   place_holder_container::place_holder_container(::ca::application * papp) :
      ca(papp),
      m_holdera(papp)
   {
   }

   place_holder_container::~place_holder_container()
   {
   }

   void place_holder_container::_001InstallMessageHandling(::user::win::message::dispatch * pdispatch)
   {
      ::user::control::_001InstallMessageHandling(pdispatch);
   }


   place_holder * place_holder_container::hold(::user::interaction * pui)
   {
      if(!m_holdera.add_new())
         return NULL;
      if(!m_holdera.last_element().create(this))
      {
         m_holdera.remove_last();
         return NULL;
      }
      if(!on_hold(pui, &m_holdera.last_element()))
      {
         m_holdera.remove_last();
         return NULL;
      }
      return &m_holdera.last_element();;
   }

   bool place_holder_container::unhold(::user::interaction * pui)
   {
      for(int i = 0; i < m_holdera.get_count(); i++)
      {
         if(m_holdera[i].is_holding(pui))
         {
            if(on_unhold(pui, &m_holdera[i]))
            {
               m_holdera.remove_at(i);
               return true;
            }
            return false;
         }
      }
      return false;
   }

   bool place_holder_container::on_hold(::user::interaction * pui, place_holder * pholder)
   {
      if(pholder->can_merge(pui))
      {
         return pholder->merge(pui);
      }
      else
      {
         return pholder->hold(pui);
      }
   }

   bool place_holder_container::on_unhold(::user::interaction * pui, place_holder * pholder)
   {
      return pholder->unhold(pui);
   }


   bool place_holder_container::create(::user::interaction * puiParent)
   {
      return ::database::user::interaction::create(NULL, NULL, AFX_WS_DEFAULT_VIEW, rect(0,0,0,0), puiParent, 100);
   }


} // namespace user