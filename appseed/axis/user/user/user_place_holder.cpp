#include "framework.h" // from "axis/user/user.h"


namespace user
{


   place_holder::place_holder(sp(::aura::application) papp) :
      element(papp),
      m_uiptraHold(papp)
   {
   }

   place_holder::~place_holder()
   {
   }

   void place_holder::install_message_handling(::message::dispatch * pdispatch)
   {
      ::user::interaction::install_message_handling(pdispatch);
   }

   bool place_holder::can_merge(sp(::user::interaction) pui)
   {

      if(m_uiptraHold.contains(pui))
         return false;

      if(m_uiptraHold.get_count() == 0)
         return false;

      return m_uiptraHold[0]->can_merge(pui);

   }


   bool place_holder::merge(sp(::user::interaction) pui)
   {

      if(!can_merge(pui))
         return false;

      if(!m_uiptraHold[0]->merge(pui))
         return false;

      m_uiptraHold.add(pui);

      return true;

   }


   bool place_holder::is_holding(sp(::user::interaction) pui)
   {

      return m_uiptraHold.contains(pui);

   }


   bool place_holder::hold(sp(::user::interaction) pui)
   {

      if(pui == NULL)
         return false;

      if(m_uiptraHold.contains(pui))
         return true;

      for(index i = m_uiptraHold.get_upper_bound(); i >= 0; i--)
      {

         System.place_hold(m_uiptraHold(i));

      }

      m_uiptraHold.remove_all();

      m_uiptraHold.add(pui);

      if(m_uiptraHold.get_count() == 1)
      {
         pui->SetParent(this);
      }

      layout();

      return true;

   }


   bool place_holder::unhold(sp(::user::interaction) pui)
   {
      if(m_uiptraHold.find_first(pui) == 0)
         return m_uiptraHold.remove_all() > 0;
      else
         return m_uiptraHold.remove(pui) >= 0;
   }

   void place_holder::layout()
   {
      if(m_uiptraHold.get_count() <= 0)
         return;

      sp(::user::interaction) puiHold = m_uiptraHold(0);

      rect rectClient;
      GetClientRect(rectClient);

      if(rectClient.area() <= 0)
         return;

      rect rectWindow;
      puiHold->GetWindowRect(rectWindow);
      ScreenToClient(rectWindow);
      if(rectWindow != rectClient)
      {
         puiHold->SetWindowPos(ZORDER_TOP, rectClient.left, rectClient.top,
            rectClient.width(), rectClient.height(), 
            (puiHold->IsWindowVisible() ? SWP_NOZORDER : SWP_SHOWWINDOW));
      }
      else
      {
         if(!puiHold->IsWindowVisible())
         {
            puiHold->ShowWindow(SW_SHOW);
         }
         puiHold->layout();
      }

   }


   bool place_holder::create_window(const RECT & rect, sp(::user::place_holder_container) pcontainer,id id)
   {

      return ::user::interaction::create_window(NULL, NULL, WS_VISIBLE | WS_CHILD /*__WS_DEFAULT_VIEW*/, rect, pcontainer, id) != FALSE;

   }


   interaction * place_holder::get_hold()
   {

      if(m_uiptraHold.get_count() <= 0)
         return NULL;

      return m_uiptraHold(0);

   }


   void place_holder::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }

   void place_holder::_001OnNcDraw(::draw2d::graphics * pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }


   int32_t place_holder_ptra::hold(sp(::user::interaction) pui)
   {

      int32_t count = 0;

      for(int32_t i = 0; i < this->get_count(); i++)
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




   int32_t place_holder_ptra::unhold(sp(::user::interaction) pui)
   {

      int32_t count = 0;

      for(int32_t i = 0; i < this->get_count(); i++)
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

   bool place_holder::is_place_holder()
   {
      return true;
   }

   bool place_holder::_001IsBackgroundBypass()
   {

      return true;

   }

} // namespace user
