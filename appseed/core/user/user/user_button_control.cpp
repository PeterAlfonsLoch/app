
#include "framework.h"


BaseButtonControl::BaseButtonControl(sp(::aura::application) papp) :
   element(papp),
   ::user::button(papp)
{
   m_iClick = 0;
   m_pimagelistNormal = NULL;
   m_pimagelistItemHover = NULL;
   m_pimagelistSubItemHover = NULL;
}

BaseButtonControl::~BaseButtonControl()
{
}

void BaseButtonControl::install_message_handling(::message::dispatch * pdispatch)
{
   button::install_message_handling(pdispatch);
}


bool BaseButtonControl::pre_create_window(::user::create_struct& cs)
{

   //cs.style |= BS_OWNERDRAW;

   return ::user::interaction::pre_create_window(cs);

}



void BaseButtonControl::_001OnDraw(::draw2d::graphics * pdc)
{
   rect rectClient;
   bool bItemHover;
   bool bSubItemHover;

   ::user::draw_context * pdrawcontext = pdc->::core::simple_chain < ::user::draw_context >::get_last();

   if(pdrawcontext != NULL)
   {
      rectClient     = pdrawcontext->m_rectClient;
      bItemHover     = pdrawcontext->m_bListItemHover;
      bSubItemHover  = pdrawcontext->m_bListSubItemHover;
   }
   else
   {
      if(get_form() != NULL)
         return;
      GetClientRect(rectClient);
      bItemHover     = get_hover() >= 0;
      bSubItemHover  = get_hover() >= 0;
   }

   point pt = rectClient.top_left();
   pt += size(1, 1);

   if(bSubItemHover)
   {
      pdc->Draw3dRect(
         rectClient,
         RGB(255, 255, 255),
         RGB(155, 155, 105));

      if(m_pimagelistSubItemHover != NULL)
      {
         m_pimagelistSubItemHover->draw(
            pdc,
            m_iImageSubItemHover,
            pt,
            0);
      }
      else if(m_pimagelistItemHover != NULL)
      {
         m_pimagelistItemHover->draw(
            pdc,
            m_iImageItemHover,
            pt,
            0);
      }
      else if(m_pimagelistNormal != NULL)
      {
         m_pimagelistNormal->draw(
            pdc,
            m_iImageNormal,
            pt,
            0);
      }
   }
   else if(bItemHover)
   {
      if(m_pimagelistItemHover != NULL)
      {
         m_pimagelistItemHover->draw(
            pdc,
            m_iImageItemHover,
            pt,
            0);
      }
      else if(m_pimagelistSubItemHover != NULL)
      {
         m_pimagelistSubItemHover->draw(
            pdc,
            m_iImageSubItemHover,
            pt,
            0);
      }
      else if(m_pimagelistNormal != NULL)
      {
         m_pimagelistNormal->draw(
            pdc,
            m_iImageNormal,
            pt,
            0);
      }
   }
   else
   {
      if(m_pimagelistNormal != NULL)
      {
         m_pimagelistNormal->draw(
            pdc,
            m_iImageNormal,
            pt,
            0);
      }
      else if(m_pimagelistItemHover != NULL)
      {
         m_pimagelistItemHover->draw(
            pdc,
            m_iImageItemHover,
            pt,
            0);
      }
      else if(m_pimagelistSubItemHover != NULL)
      {
         m_pimagelistSubItemHover->draw(
            pdc,
            m_iImageSubItemHover,
            pt,
            0);
      }
   }

}



void BaseButtonControl::update_drawing_objects()
{
   rect rectClient;

   GetClientRect(rectClient);


}



void BaseButtonControl::_003CustomWindowProc(signal_details * pobj)
{
  return _user_message_handler(pobj);
}


