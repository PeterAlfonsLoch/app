#include "framework.h"


namespace userbase
{


   button::button(::ca::application * papp) :
      ::user::interaction(papp), 
      ::user::button(papp),
      ca(papp),
      m_dib(papp)
   {
      m_pschema   = NULL;
   }

   button::~button()
   {
   }

   ::ca::font * button::_001GetFont()
   {
      if(m_pschema == NULL)
         return NULL;
      return m_pschema->m_font;
   }

   void button::_001OnDraw(::ca::graphics * pdc)
   {
      
      if(m_pschema == NULL)
         return;

      
      rect rectClient;
      m_pguie->GetClientRect(rectClient);

      COLORREF crBk;
      if(!_001IsWindowEnabled())
      {
         crBk = m_pschema->m_crBkDisabled;
      }
      else if(_001IsPressed())
      {
         crBk = m_pschema->m_crBkPress;
      }
      else if(m_iHover >= 0)
      {
         crBk = m_pschema->m_crBkHover;
      }
      else
      {
         crBk = m_pschema->m_crBkNormal;
      }


      if(::user::button::_001IsTranslucent())
      {
         class imaging & imaging = System.imaging();
         imaging.color_blend(
            pdc,
            rectClient,
            crBk,
            127);
      }
      else
      {
         pdc->FillSolidRect(rectClient, crBk);
      }


      COLORREF crBorder;
      if(!_001IsWindowEnabled())
      {
         crBorder = ARGB(255, 127, 127, 127);
      }
      else if(_001IsPressed())
      {
         crBorder = ARGB(255, 255, 255, 255);
      }
      else if(m_iHover >= 0)
      {
         crBorder = ARGB(255, 100, 100, 200);
      }
      else
      {
         crBorder = ARGB(255, 10, 10, 100);
      }

      if(m_pschema->m_bBorder)
      {
         pdc->Draw3dRect(rectClient, crBorder, crBorder);
      }
      
      pdc->SetBkMode(TRANSPARENT);

      rectClient.left   += 3;
      rectClient.top    += 3;
      rect rectText = m_rectText;
//      string str = gen::international::utf8_to_unicode(str);
      if(m_dib.is_set())
      {
         if(m_dib->width() > 0 &&
            m_dib->height() > 0)
         {
            rect rectDib;
            rectDib = m_rectText;
            rectDib.bottom = min(rectText.top + m_dib->height(), rectText.bottom);
            rectDib.right = min(rectText.left + m_dib->width(), rectText.right);
            //m_dib->to(pdc, rectDib);
            m_dib->bitmap_blend(pdc, rectDib);
            rectText.left += m_dib->width();
         }
      }


      if(!_001IsWindowEnabled())
      {
         pdc->SetTextColor(m_pschema->m_crTextDisabled);
      }
      else if(_001IsPressed())
      {
         pdc->SetTextColor(m_pschema->m_crTextPress);
      }
      else if(m_iHover >= 0)
      {
         pdc->SetTextColor(m_pschema->m_crTextHover);
      }
      else
      {
         pdc->SetTextColor(m_pschema->m_crTextNormal);
      }


      string strText(m_istrButtonText);
      pdc->SelectObject(m_pschema->m_font);
      pdc->draw_text(strText, rectText, DT_LEFT | DT_TOP);

   }

   void button::_001OnCreate(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      m_pschema   = &userbase::GetUfeSchema(get_app())->m_button;
   }

   void button::ResizeToFit()
   {
      ::ca::graphics * pdc = m_pguie->GetDC();

      if(pdc == NULL)
         return;

      pdc->SelectObject(m_pschema->m_font);

      string strText(m_istrButtonText);
      size size = pdc->GetTextExtent(strText);

      rect rect(0, 0, 0, 0);
      rect.right = size.cx / 0.77 + 4;
      rect.bottom = size.cy / 0.77 + 4;

      SetWindowPos(NULL, 0, 0, rect.width(), rect.height(), SWP_NOMOVE);

      m_pguie->ReleaseDC(pdc);


   }

   void button::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      ::user::button::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE                  , pinterface, this, &button::_001OnCreate);
   }


} // namespace userbase


