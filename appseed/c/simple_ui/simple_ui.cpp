#include "framework.h"


#ifdef WINDOWS
#include <GdiPlus.h>
#endif


simple_ui::simple_ui()
{
   
   m_puiParent    = NULL;
   m_bVisible     = true;
   m_puiFocus     = NULL;

}

simple_ui::~simple_ui()
{
}


void simple_ui::set_parent(simple_ui * puiParent)
{
   
   if(m_puiParent != NULL && m_puiParent != puiParent)
   {
      
      for(int i = 0; i < m_puiParent->m_uiptra.get_count(); i++)
      {
         
         if(m_puiParent->m_uiptra[i] == this)
         {
            
            m_puiParent->m_uiptra.remove_at(i);
            break;

         }

      }

   }

   m_puiParent = puiParent;

   if(m_puiParent != NULL)
   {
      
      m_puiParent->m_uiptra.add(this);

   }

}


void simple_ui::draw(HDC hdc)
{

   if(m_bVisible)
   {

      draw_children(hdc);

      draw_this(hdc);

   }

}

void simple_ui::draw_this(HDC hdc)
{

   Gdiplus::Graphics graphics2(hdc);

   graphics2.SetCompositingMode(Gdiplus::CompositingModeSourceOver);

   Gdiplus::SolidBrush br(Gdiplus::Color(84, 84, 84, 77));

   graphics2.FillRectangle(&br, m_rect.left, m_rect.top, width(&m_rect), height(&m_rect));

}

void simple_ui::draw_children(HDC hdc)
{
   
   for(int i = 0; i = m_uiptra.get_count(); i++)
   {
      
      try
      {

         m_uiptra[i]->draw(hdc);

      }
      catch(...)
      {

      }

   }

}




void simple_ui::on_action(const char * pszId)
{
   
   if(m_puiParent != NULL)
   {

      m_puiParent->on_action(pszId);

   }

}



bool simple_ui::is_focusable()
{
   return false;
}



void simple_ui::focus_next()
{

   for(int i = 0; i < m_puiParent->m_uiptra.get_count(); i++)
   {
      
      if(m_puiParent->m_uiptra[i]->is_focusable())
      {
         
         m_puiParent->set_focus(m_puiParent->m_uiptra[i]);

         break;

      }

   }

}


void simple_ui::set_focus(simple_ui * pui)
{
   
   if(m_puiParent == NULL)
   {

      m_puiFocus = pui;

   }
   else
   {

      m_puiParent->set_focus(pui);

   }

}


simple_ui * simple_ui::get_focus()
{

   if(m_puiParent == NULL)
   {

      return m_puiFocus;

   }
   else
   {

      return m_puiParent->get_focus();

   }


}


bool simple_ui::is_visible()
{
   
   return m_bVisible && (m_puiParent == NULL || m_puiParent->is_visible());

}