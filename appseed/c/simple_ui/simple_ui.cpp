#include "framework.h"


simple_ui::simple_ui()
{

   m_puiParent    = NULL;
   m_bVisible     = true;
   m_puiFocus     = NULL;
   m_pplugin      = NULL;

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


void simple_ui::draw(simple_graphics & g)
{

   if(m_bVisible)
   {

      draw_this(g);

      draw_children(g);

   }

}


void simple_ui::draw_children(simple_graphics & g)
{

   for(int i = 0; i < m_uiptra.get_count(); i++)
   {

      try
      {

         m_uiptra[i]->draw(g);

      }
      catch(...)
      {

      }

   }

}

void simple_ui::on_char(int ch, UINT uScan)
{

   get_focus()->on_char(ch, uScan);

}


void simple_ui::on_lbutton_down(int x, int y)
{

   for(int i = 0; i < m_uiptra.get_count(); i++)
   {

      if(x >= m_uiptra[i]->m_rect.left
      && x <= m_uiptra[i]->m_rect.right
      && y >= m_uiptra[i]->m_rect.top
      && y <= m_uiptra[i]->m_rect.bottom)
      {

         m_uiptra[i]->on_lbutton_down(x, y);

      }

   }

}

void simple_ui::on_lbutton_up(int x, int y)
{

   for(int i = 0; i < m_uiptra.get_count(); i++)
   {

      if(x >= m_uiptra[i]->m_rect.left
      && x <= m_uiptra[i]->m_rect.right
      && y >= m_uiptra[i]->m_rect.top
      && y <= m_uiptra[i]->m_rect.bottom)
      {

         m_uiptra[i]->on_lbutton_up(x, y);

      }

   }

}


void simple_ui::on_mouse_move(int x, int y)
{

   for(int i = 0; i < m_uiptra.get_count(); i++)
   {

      if(x >= m_uiptra[i]->m_rect.left
      && x <= m_uiptra[i]->m_rect.right
      && y >= m_uiptra[i]->m_rect.top
      && y <= m_uiptra[i]->m_rect.bottom)
      {

         m_uiptra[i]->on_mouse_move(x, y);

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

   ::count iFind = m_puiParent->m_uiptra.get_count() - 1;

   for(int i = 0; i < m_puiParent->m_uiptra.get_count(); i++)
   {

      if(m_puiParent->m_uiptra[i] == this)
      {

         iFind = i;

         break;

      }

   }

   for(::index i = iFind + 1; i < m_puiParent->m_uiptra.get_count(); i++)
   {

      if(m_puiParent->m_uiptra[i]->is_focusable())
      {

         m_puiParent->set_focus(m_puiParent->m_uiptra[i]);

         return;

      }

   }

   for(int i = 0; i <= iFind; i++)
   {

      if(m_puiParent->m_uiptra[i]->is_focusable())
      {

         m_puiParent->set_focus(m_puiParent->m_uiptra[i]);

         return;

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


::hotplugin::plugin * simple_ui::get_plugin()
{

   if(m_pplugin != NULL)
      return m_pplugin;

   if(m_puiParent == NULL)
      return NULL;

   return m_puiParent->get_plugin();

}
