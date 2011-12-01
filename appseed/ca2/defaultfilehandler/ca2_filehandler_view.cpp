#include "StdAfx.h"


namespace ca2
{


   namespace filehandler
   {


      view::view(::ca::application * papp) :
         ca(papp),
         ::user::interaction(papp),
         ::userbase::view(papp),
         ::user::scroll_view(papp),
         ::userbase::scroll_view(papp),
         ::userbase::form_view(papp),
         ::user::form(papp),
         html_form(papp),
         html_form_view(papp),
         form_view(papp),
         m_document(papp)
      {

         ::ca::font_sp font(get_app());

         font->CreatePointFont(140, "Geneva");

         SetFont(font);

      }
   
      void view::install_message_handling(::user::win::message::dispatch * pinterface)
      {
         form_view::install_message_handling(pinterface);
         IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
         IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);
         IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
      }

      void view::refresh()
      {
         m_list.parse(&System.filehandler(), System.file().extension(m_strName));
         layout();
      }

      void view::_001OnTimer(gen::signal_object * pobj)
      {
         SCAST_PTR(user::win::message::timer, ptimer, pobj);
         if(ptimer->m_nIDEvent == 1984)
         {
            refresh();
         }
      }

      void view::_001OnCreate(gen::signal_object * pobj)
      {
      
         if(pobj->previous())
            return;

         SetTimer(1984, 1984 + 1977, NULL);

      }

      void view::item::parse(const char * pszApp)
      {
         m_strApp = pszApp;
      }

      void view::list::parse(handler * phandler, const char * pszTopic)
      {
         
         remove_all();

         stringa straApp;

         phandler->get_extension_app(straApp, pszTopic);

         item item;

         for(int i = 0; i < straApp.get_count(); i++)
         {
            item.parse(straApp[i]);
            item.m_iIndex = i;
            add(item);
         }

      }

      void view::draw_item::draw(view * pview, ::ca::graphics * pdc, list * plist, item * pitem)
      {
         COLORREF cr;
         ::ca::application * papp = pview->get_app();
         bool bHover = pview->m_iHover == pitem->m_iIndex;
         cr = bHover ? RGB(230, 255, 230) : RGB(200, 255, 200);
         if(!Sys(papp).savings().is_trying_to_save(gen::resource_processing)
         && !Sys(papp).savings().is_trying_to_save(gen::resource_display_bandwidth)
         && !Sys(papp).savings().is_trying_to_save(gen::resource_memory))
         {
            class imaging & imaging = Sys(papp).imaging();
            imaging.color_blend(pdc, m_rectItem, cr, 127);
         }
         else
         {
            pdc->FillSolidRect(m_rectItem, cr);
         }
         cr = bHover ? RGB(150, 255, 150) : RGB(50, 255, 50);
         pdc->FillSolidRect(m_rectStatusImage, cr);
         COLORREF cr1;
         COLORREF cr2;
         if(bHover)
         {
            cr = RGB(0, 100, 0);
            cr1 = RGB(120, 255, 150);
            cr2 = RGB(23, 200, 33);
         }
         else
         {
            cr = RGB(40, 40, 40);
            cr1 = RGB(100, 100, 100);
            cr2 = RGB(10, 10, 10);
         }
         pdc->Draw3dRect(m_rectItem, cr1, cr2);
         cr |= 0xff000000;
         pdc->set_color(cr);
         pdc->DrawText(pitem->m_strApp, m_rectName, DT_LEFT | DT_BOTTOM);
      }


      view::draw_list::draw_list()
      {
         m_iItemHeight = 30;
      }

      void view::draw_list::layout(LPCRECT lpcrect, list * plist)
      {
         remove_all();
         draw_item item;
         int top = lpcrect->top;
         for(int i = 0; i < plist->get_count(); i++)
         {
            item.m_rectItem.left = lpcrect->left;
            item.m_rectItem.right = lpcrect->right;
            item.m_rectItem.top = top;
            item.m_rectItem.bottom = item.m_rectItem.top + m_iItemHeight;
            top = item.m_rectItem.bottom + 2;
            item.m_rectStatusImage = item.m_rectItem;
            item.m_rectStatusImage.right = item.m_rectStatusImage.left + m_iItemHeight;
            item.m_rectStatusImage.deflate(2, 2);
            item.m_rectName = item.m_rectItem;
            item.m_rectName.left = item.m_rectStatusImage.right;
            item.m_rectName.deflate(2, 2);
            add(item);
         }
      }

      void view::draw_list::draw(view * pview, ::ca::graphics * pdc, list * plist)
      {
         for(int i = 0; i < get_count(); i++)
         {
            element_at(i).draw(pview, pdc, plist, &plist->element_at(i));
         }
      }


      void view::layout()
      {
         ::ca::graphics * pdc = GetDC();
         rect rectClient;
         GetClientRect(rectClient);
         m_drawlist.layout(rectClient, &m_list);
         ReleaseDC(pdc);
      }

      void view::_001OnDraw(::ca::graphics * pdc)
      {

         pdc->set_font(GetFont());
         m_drawlist.draw(this, pdc, &m_list);

      }

      void view::_001OnLButtonUp(gen::signal_object * pobj)
      {

         SCAST_PTR(user::win::message::mouse, pmouse, pobj);

         e_element eelement;
         int iItem = hit_test(pmouse->m_pt, eelement);
         if(iItem >= 0)
         {
            string strRequest;
            strRequest = "ca2app://" + m_list[iItem].m_strApp + "/" + m_strName;
            Bergedge.request(var(strRequest));
         }

      }

      int view::hit_test(point pt, e_element & eelement)
      {
         ScreenToClient(&pt);
         for(int i = 0; i < m_drawlist.get_count(); i++)
         {
            if(m_drawlist[i].m_rectName.contains(pt))
            {
               eelement = element_text;
               return i;
            }
            if(m_drawlist[i].m_rectStatusImage.contains(pt))
            {
               eelement = element_status_image;
               return i;
            }
            if(m_drawlist[i].m_rectItem.contains(pt))
            {
               eelement = element_area;
               return i;
            }
         }
         eelement = element_none;
         return -1;
      }

   } // namespace filehandler


} // namespace mail


