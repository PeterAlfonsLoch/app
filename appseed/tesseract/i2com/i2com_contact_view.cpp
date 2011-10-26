#include "StdAfx.h"

namespace i2com
{

   contact_view::contact_view(::ca::application * papp) :
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
      ::form_view(papp),
      m_document(papp)
   {
   }
   
   void contact_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      form_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &contact_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &contact_view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &contact_view::_001OnLButtonUp);
   }

   void contact_view::refresh()
   {
      m_document.load(Application.file().as_string("http://i2com.api.veriterse.net/contact"));
      m_list.parse(&m_document);
      layout();
   }

   void contact_view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 1984)
      {
         refresh();
      }
   }

   void contact_view::_001OnCreate(gen::signal_object * pobj)
   {
      
      if(pobj->previous())
         return;

      SetTimer(1984, 1984 + 1977, NULL);

   }

   void contact_view::contact::parse(::xml::node * pnode)
   {
      m_strId              = pnode->attr("id");
      m_strName            = pnode->attr("name");
      m_strPresenceStatus  = pnode->attr("presence");
      m_strEmail           = pnode->attr("email");
   }

   void contact_view::contact_list::parse(::xml::document * pdoc)
   {
      remove_all();
      ::xml::node * plist = pdoc->get_root();
      if(plist->attr("presence") == "not_licensed")
      {
         m_bUserPresenceLicensed = false;
      }
      else
      {
         m_bUserPresenceLicensed = true;
      }
      int iCount = plist->get_children_count();
      contact contact;
      for(int i = 0; i < iCount; i++)
      {
         ::xml::node * pchild = plist->child_at(i);
         if(pchild->m_strName == "contact")
         {
            contact.parse(pchild);
            contact.m_iIndex = i;
            add(contact);
         }
      }
   }

   void contact_view::draw_contact::draw(::i2com::contact_view * pview, ::ca::graphics * pdc, contact_list * plist, contact * pcontact)
   {
      COLORREF cr;
      ::ca::application * papp = pview->get_app();
      bool bHover = pview->m_iHover == pcontact->m_iIndex;
      if(plist->m_bUserPresenceLicensed)
      {
         if(pcontact->m_strPresenceStatus.CompareNoCase("online") == 0)
         {
            cr = bHover ? RGB(230, 255, 230) : RGB(200, 255, 200);
            if(!Sys(papp).savings().is_trying_to_save(gen::resource_processing)
            && !Sys(papp).savings().is_trying_to_save(gen::resource_display_bandwidth)
            && !Sys(papp).savings().is_trying_to_save(gen::resource_memory))
            {
               class imaging & imaging = Sys(papp).imaging();
               imaging.color_blend(pdc, m_rectStatusImage, cr, 127);
            }
            else
            {
               pdc->FillSolidRect(m_rectItem, cr);
            }
            cr = bHover ? RGB(150, 255, 150) : RGB(50, 255, 50);
            pdc->FillSolidRect(m_rectStatusImage, cr);
         }
         else
         {
            cr = bHover ? RGB(240, 240, 240) : RGB(190, 190, 190);
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
            cr = bHover ? RGB(80, 80, 80) : RGB(127, 127, 127);
            pdc->FillSolidRect(m_rectStatusImage, cr);
         }
      }
      else
      {
         cr = bHover ? RGB(240, 240, 240) : RGB(190, 190, 190);
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
         cr = bHover ? RGB(80, 80, 80) : RGB(127, 127, 127);
         pdc->FillSolidRect(m_rectStatusImage, cr);
      }
      COLORREF cr1;
      COLORREF cr2;
      if(plist->m_bUserPresenceLicensed && pcontact->m_strPresenceStatus.CompareNoCase("online") == 0 && bHover)
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
      pdc->SetBkMode(TRANSPARENT);
      pdc->SetTextColor(cr);
      pdc->DrawText(pcontact->m_strName, m_rectName, DT_LEFT | DT_BOTTOM);
   }


   contact_view::draw_contact_list::draw_contact_list()
   {
      m_iItemHeight = 30;
   }

   void contact_view::draw_contact_list::layout(LPCRECT lpcrect, contact_list * plist)
   {
      remove_all();
      draw_contact contact;
      int top = lpcrect->top;
      for(int i = 0; i < plist->get_count(); i++)
      {
         contact.m_rectItem.left = lpcrect->left;
         contact.m_rectItem.right = lpcrect->right;
         contact.m_rectItem.top = top;
         contact.m_rectItem.bottom = contact.m_rectItem.top + m_iItemHeight;
         top = contact.m_rectItem.bottom + 2;
         contact.m_rectStatusImage = contact.m_rectItem;
         contact.m_rectStatusImage.right = contact.m_rectStatusImage.left + m_iItemHeight;
         contact.m_rectStatusImage.deflate(2, 2);
         contact.m_rectName = contact.m_rectItem;
         contact.m_rectName.left = contact.m_rectStatusImage.right;
         contact.m_rectName.deflate(2, 2);
         add(contact);
      }
   }

   void contact_view::draw_contact_list::draw(::i2com::contact_view * pview, ::ca::graphics * pdc, contact_list * plist)
   {
      for(int i = 0; i < get_count(); i++)
      {
         element_at(i).draw(pview, pdc, plist, &plist->element_at(i));
      }
   }


   void contact_view::layout()
   {
      ::ca::graphics * pdc = GetDC();
      rect rectClient;
      GetClientRect(rectClient);
      m_drawlist.layout(rectClient, &m_list);
      ReleaseDC(pdc);
   }

   void contact_view::_001OnDraw(::ca::graphics * pdc)
   {

      m_drawlist.draw(this, pdc, &m_list);

   }

   void contact_view::_001OnLButtonUp(gen::signal_object * pobj)
   {

      SCAST_PTR(user::win::message::mouse, pmouse, pobj);

      e_element eelement;
      int iItem = hit_test(pmouse->m_pt, eelement);
      if(iItem >= 0)
      {
         string strLink;
         strLink = "i2com://" + m_list[iItem].m_strId + "/im/";
         get_html_data()->open_link(strLink);
      }

   }

   int contact_view::hit_test(point pt, e_element & eelement)
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

} // namespace i2com