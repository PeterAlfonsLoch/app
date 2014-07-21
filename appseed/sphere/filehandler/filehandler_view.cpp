#include "framework.h"


namespace filehandler
{


   view::view(sp(::base::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::user::form(papp),
      html_form(papp),
      html_form_view(papp),
      form_view(papp),
      m_document(papp)
   {

      ::draw2d::font_sp font(allocer());

      font->create_point_font("Geneva", 14.0);

      SetFont(font);

   }

   void view::install_message_handling(::message::dispatch * pinterface)
   {
      form_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &view::_001OnLButtonUp);
   }

   void view::refresh()
   {
      
      m_plistWorking = canew(list(get_app()));
      
      m_plistWorking->parse(&System.filehandler(), System.file().extension(m_strName));
      
      m_plist = m_plistWorking;

      m_plistWorking = NULL;

      layout();

   }

   void view::_001OnTimer(signal_details * pobj)
   {
      SCAST_PTR(::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 8888)
      {
         refresh();
      }
   }

   void view::_001OnCreate(signal_details * pobj)
   {

      if(pobj->previous())
         return;

      SetTimer(8888, 5000, NULL);

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

      item item(get_app());

      for(int32_t i = 0; i < straApp.get_count(); i++)
      {
         item.parse(straApp[i]);
         item.m_iIndex = i;
         add(canew(class item(item)));
      }

   }

   view::item::item(sp(::base::application) papp) :
      element(papp)
   {

   }

   void view::item::draw(sp(view) pview, ::draw2d::graphics * pdc, list * plist)
   {

      UNREFERENCED_PARAMETER(plist);

      COLORREF cr;
      sp(::base::application) papp = pview->get_app();
      bool bHover = pview->m_iHover == m_iIndex;
      cr = bHover ? ARGB(255, 230, 255, 230) : ARGB(255, 200, 255, 200);
      if(!Sys(papp).savings().is_trying_to_save(::base::resource_processing)
         && !Sys(papp).savings().is_trying_to_save(::base::resource_display_bandwidth)
         && !Sys(papp).savings().is_trying_to_save(::base::resource_memory))
      {
         class imaging & imaging = Sys(papp).visual().imaging();
         imaging.color_blend(pdc, m_rectItem, cr, 127);
      }
      else
      {
         pdc->FillSolidRect(m_rectItem, cr);
      }
      cr = bHover ? ARGB(255, 150, 255, 150) : ARGB(255, 50, 255, 50);
      pdc->FillSolidRect(m_rectStatusImage, cr);
      COLORREF cr1;
      COLORREF cr2;
      if(bHover)
      {
         cr = ARGB(255, 0, 100, 0);
         cr1 = ARGB(255, 120, 255, 150);
         cr2 = ARGB(255, 23, 200, 33);
      }
      else
      {
         cr = ARGB(255, 40, 40, 40);
         cr1 = ARGB(255, 100, 100, 100);
         cr2 = ARGB(255, 10, 10, 10);
      }
      pdc->Draw3dRect(m_rectItem, cr1, cr2);
      cr |= 0xff000000;
      ::draw2d::brush_sp brushText(allocer());
      brushText->create_solid(cr);
      //pdc->set_color(cr);
      pdc->draw_text(m_strApp, m_rectName, DT_LEFT | DT_BOTTOM);
   }


   view::list::list(sp(::base::application) papp) :
      element(papp)
   {
      m_iItemHeight = 30;
   }

   void view::list::layout(LPCRECT lpcrect)
   {
      int32_t top = lpcrect->top;
      for(int32_t i = 0; i < get_count(); i++)
      {
         item & item = operator[](i);
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
         
      }
   }

   void view::list::draw(sp(view) pview, ::draw2d::graphics * pdc)
   {
      for(int32_t i = 0; i < get_count(); i++)
      {
         element_at(i)->draw(pview, pdc, this);
      }
   }


   void view::layout()
   {

      if (m_plist.is_null())
         return;

      layout_list(m_plist);

      
   }

   void view::layout_list(list * plist)
   {
      
      ::draw2d::memory_graphics pdc(allocer());

      rect rectClient;

      GetClientRect(rectClient);

      plist->layout(rectClient);

   }


   void view::_001OnDraw(::draw2d::graphics * pdc)
   {

      if (m_plist.is_null())
         return;

      pdc->set_font(GetFont());

      m_plist->draw(this, pdc);


   }



   void view::_001OnLButtonUp(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      e_element eelement;

      index iItem = hit_test(pmouse->m_pt, eelement);

      if(iItem >= 0)
      {

         /*
         var varRequest;

         varRequest = "app://" + m_list[iItem].m_strApp + "/" + m_strName;

         session().request(varRequest);
         */

         sp(::create_context) createcontext(allocer());

         createcontext->m_spCommandLine->m_strApp = m_plist->operator [](iItem).m_strApp;

         createcontext->m_spCommandLine->m_varFile                = m_strName;

         session().request_create(createcontext);

         //varFile = createcontext->m_spCommandLine->m_varFile;

      }

   }

   index view::hit_test(point pt, e_element & eelement)
   {


      if (m_plist.is_null())
         return -1;

      ScreenToClient(&pt);
      for(int32_t i = 0; i < m_plist->get_count(); i++)
      {
         if(m_plist->element_at(i)->m_rectName.contains(pt))
         {
            eelement = element_text;
            return i;
         }
         if (m_plist->element_at(i)->m_rectStatusImage.contains(pt))
         {
            eelement = element_status_image;
            return i;
         }
         if (m_plist->element_at(i)->m_rectItem.contains(pt))
         {
            eelement = element_area;
            return i;
         }
      }
      eelement = element_none;
      return -1;
   }

} // namespace filehandler




