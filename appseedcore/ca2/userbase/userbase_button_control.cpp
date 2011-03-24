
#include "StdAfx.h"


BaseButtonControl::BaseButtonControl(::ca::application * papp) :
   ca(papp),
   ::user::button(papp),
   ::userbase::button(papp)
{
   m_iClick = 0;
   m_pimagelistNormal = NULL;
   m_pimagelistItemHover = NULL;
   m_pimagelistSubItemHover = NULL;
}

BaseButtonControl::~BaseButtonControl()
{
}

void BaseButtonControl::_001InstallMessageHandling(::user::win::message::dispatch * pdispatch)
{
   button::_001InstallMessageHandling(pdispatch);
}


BOOL BaseButtonControl::PreCreateWindow(CREATESTRUCT& cs) 
{
   cs.style |= BS_OWNERDRAW;
   return ::user::interaction::PreCreateWindow(cs);
}



void BaseButtonControl::_001OnDraw(::ca::graphics * pdc)
{
   rect rectClient;
   bool bItemHover;
   bool bSubItemHover;

   if(pdc->draw_context() != NULL)
   {
      rectClient = pdc->draw_context()->m_rectClient;
      bItemHover = pdc->draw_context()->m_bItemHover;
      bSubItemHover = pdc->draw_context()->m_bSubItemHover;
   }
   else
   {
      if(get_form() != NULL)
         return;
      GetClientRect(rectClient);
      bItemHover = get_hover() >= 0;
      bSubItemHover = get_hover() >= 0;
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



void BaseButtonControl::UpdateDrawingObjects()
{
   rect rectClient;

   GetClientRect(rectClient);


}



void BaseButtonControl::_003CustomWindowProc(gen::signal_object * pobj)
{
  return _user_message_handler(pobj);
}


