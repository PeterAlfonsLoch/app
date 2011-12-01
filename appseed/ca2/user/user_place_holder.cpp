#include "StdAfx.h"


namespace user
{

   place_holder::place_holder(::ca::application * papp) :
      ca(papp)
   {
   }

   place_holder::~place_holder()
   {
   }

   void place_holder::install_message_handling(::gen::message::dispatch * pdispatch)
   {
      ::user::control::install_message_handling(pdispatch);
   }

   bool place_holder::can_merge(::user::interaction * pui)
   {
      if(m_uiptraHold.contains(pui))
         return false;
      if(m_uiptraHold.get_count() == 0)
         return false;
      return m_uiptraHold[0]->can_merge(pui);
   }

   bool place_holder::merge(::user::interaction * pui)
   {
      if(!can_merge(pui))
         return false;
      if(!m_uiptraHold[0]->merge(pui))
         return false;
      m_uiptraHold.add(pui);
      return true;
   }

   bool place_holder::is_holding(::user::interaction * pui)
   {
      return m_uiptraHold.contains(pui);
   }

   bool place_holder::hold(::user::interaction * pui)
   {
      if(pui == NULL)
      {
         return false;
      }
      if(m_uiptraHold.contains(pui))
         return true;
      for(int i = m_uiptraHold.get_upper_bound(); i >= 0; i--)
      {
         System.hold(m_uiptraHold[i]);
      }
      m_uiptraHold.remove_all();
      m_uiptraHold.add(pui);
      if(m_uiptraHold.get_count() == 1)
      {
         pui->SetParent(this);
      }
      //layout();
      return true;
   }

   bool place_holder::unhold(::user::interaction * pui)
   {
      if(m_uiptraHold.find(pui) == 0)
         return m_uiptraHold.remove_all() > 0;
      else
         return m_uiptraHold.remove(pui) >= 0;
   }

   void place_holder::layout()
   {
      if(m_uiptraHold.get_count() <= 0)
         return;

      ::user::interaction * puiHold = m_uiptraHold[0];

      rect rectClient;
      GetClientRect(rectClient);

      rect rectWindow;
      puiHold->GetWindowRect(rectWindow);
      ScreenToClient(rectWindow);
      if(rectWindow != rectClient)
      {
         puiHold->SetWindowPos(ZORDER_TOP, rectClient.left, rectClient.top,
            rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
      }
      else
      {
         puiHold->ShowWindow(SW_SHOW);
         puiHold->layout();
      }


   }

   bool place_holder::create(place_holder_container * pcontainer, id id)
   {
      return ::database::user::interaction::create(NULL, NULL, AFX_WS_DEFAULT_VIEW, rect(0,0,0,0), pcontainer, id) != FALSE;
   }

   interaction * place_holder::get_ui()
   {
      if(m_uiptraHold.get_count() <= 0)
         return NULL;
      return m_uiptraHold[0];
   }

   int place_holder_ptra::hold(::user::interaction * pui)
   {

      int count = 0;

      for(int i = 0; i < this->get_count(); i++)
      {
         try
         {
            if(this->element_at(i)->hold(pui))
            {
               count++;
            }
         }
         catch(...)
         {
         }
      }

      return count;

   }

   int place_holder_ptra::unhold(::user::interaction * pui)
   {

      int count = 0;

      for(int i = 0; i < this->get_count(); i++)
      {
         try
         {
            if(this->element_at(i)->unhold(pui))
            {
               count++;
            }
         }
         catch(...)
         {
         }
      }

      return count;

   }


} // namespace user
