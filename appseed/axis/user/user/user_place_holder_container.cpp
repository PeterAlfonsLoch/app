#include "framework.h" // from "axis/user/user.h"


namespace user
{

   place_holder_container::place_holder_container(sp(::aura::application) papp) :
      element(papp),
      m_holdera(papp)
   {
   }

   place_holder_container::~place_holder_container()
   {
   }

   void place_holder_container::install_message_handling(::message::dispatch * pdispatch)
   {
      ::user::interaction::install_message_handling(pdispatch);
   }


   sp(place_holder)place_holder_container::get_new_place_holder(const RECT & rectCreate)
   {
      
      m_holdera.add(new place_holder(get_app()));
      
      if(m_holdera.last_element().is_null())
         return NULL;

      if(!m_holdera.last_element()->::user::interaction::create_window(NULL, NULL,WS_VISIBLE | WS_CHILD /*__WS_DEFAULT_VIEW*/,rectCreate,(sp(::user::place_holder_container))this,m_holdera.get_upper_bound()))
      {

         m_holdera.remove_last();

         return NULL;

      }

      return m_holdera.last_element();

   }


   bool place_holder_container::remove_place_holder(sp(place_holder) pholder)
   {
      bool bRemove = m_holdera.remove(pholder) > 0;
      return bRemove;
   }

   sp(place_holder) place_holder_container::place(::user::interaction * pui,const RECT & rectCreate)
   {
      sp(place_holder) pholder = get_new_place_holder(rectCreate);
      if(!on_hold(pui, pholder))
      {
         remove_place_holder(pholder);
         return NULL;
      }
      return pholder;
   }


   bool place_holder_container::unplace(::user::interaction * pui)
   {
      for(int32_t i = 0; i < m_holdera.get_count(); i++)
      {
         if(m_holdera[i]->is_holding(pui))
         {
            if(on_unhold(pui, m_holdera[i]))
            {
               m_holdera.remove_at(i);
               return true;
            }
            return false;
         }
      }
      return false;
   }

   bool place_holder_container::on_hold(::user::interaction * pui, sp(place_holder) pholder)
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

   bool place_holder_container::on_unhold(::user::interaction * pui, sp(place_holder) pholder)
   {
      return pholder->unhold(pui);
   }


   bool place_holder_container::create_window(const RECT & rect, ::user::interaction * puiParent,id id)
   {
      return ::user::interaction::create_window(NULL, NULL,0 /*__WS_DEFAULT_VIEW*/,rect,puiParent,id) != FALSE;
   }

   place_holder_ptra place_holder_container_ptra::place(::user::interaction * pui,const RECT & rectCreate)
   {
      place_holder_ptra holderptra;
      sp(place_holder) pholder;
      for(int32_t i = 0; i < this->get_count(); i++)
      {
         pholder = this->element_at(i)->place(pui,rectCreate);
         if(pholder != NULL)
         {
            holderptra.add(pholder);
         }
      }
      return holderptra;
   }

   int32_t place_holder_container_ptra::unplace(::user::interaction * pui)
   {
      int32_t count = 0;
      for(int32_t i = 0; i < this->get_count(); i++)
      {
         if(this->element_at(i)->unplace(pui))
         {
            count++;
         }
      }
      return count;
   }

} // namespace user
