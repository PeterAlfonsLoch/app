#include "framework.h"

namespace userbase
{

   form_view::form_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::userbase::scroll_view(papp),
      ::user::form(papp)
   {
   }

   form_view::~form_view()
   {
   }

   void form_view::install_message_handling(::ca::message::dispatch * pinterface)
   {
      ::userbase::scroll_view::install_message_handling(pinterface);
      ::user::form::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &form_view::_001OnCreate);

   //   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
   //   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
   //   IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
     // IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);
      //IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &::user::interaction::_001OnTimer);

   //  IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &form_view::_001OnLButtonDown);
   //   IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &form_view::_001OnMouseMove);
   //   IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &form_view::_001OnLButtonUp);

   }

   /*
   bool form_view::open_document(const char * lpszPathName)
   {
      string strPathName(lpszPathName);
      if(strPathName.Mid(3) == "wb:")
         return FALSE;
      string str = Application.file().as_string(lpszPathName);
      if(str.is_empty())
      {
         System.sync_load_url(str, lpszPathName, &ApplicationUser, mm_pcookies);
      }
      m_strPathName = lpszPathName;
      get_html_data()->m_strPathName = m_strPathName;
      get_html_data()->load(str);
      layout();
      return TRUE;

   }
   */

   /*
   void form_view::layout()
   {
      if(m_pcontainer == NULL)
         return;
      GetClientRect(&get_html_data()->m_rect);
      bool bLayoutOk = false;
      if(get_html_data()->m_rect.width() > 0 &&
         get_html_data()->m_rect.height() > 0)
      {
         bLayoutOk = true;
      }
      ::ca::client_graphics pdc(this);
      get_html_data()->m_pguie = this;
      get_html_data()->m_pguie = this;
      get_html_data()->implement(pdc);
      if(bLayoutOk)
      {
         get_html_data()->layout(pdc);
      }
      
      if(bLayoutOk)
      {
         _001RedrawWindow();
      }

   }
   */

      void form_view::_001OnCreate(ca::signal_object * pobj)
      {
         pobj->previous();
     }


   /*
     void form_view::_001OnLButtonDown(ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::mouse, pmouse, pobj);
      point pt;
      pt = pmouse->m_pt;
      ScreenToClient(&pt);
      m_pelementalLButtonDown = get_html_data()->m_elemental.hit_test(pt);
      if(m_pelementalLButtonDown != NULL)
      {
         html::signal signal(pobj->m_psignal);
         signal.m_pdoccontainer = m_pcontainer;
         signal.m_psignal = pmouse;
         m_pelementalLButtonDown->OnLButtonDown(&signal);
      }
   }

   void form_view::_001OnMouseMove(ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::mouse, pmouse, pobj);
      point pt;
      pt = pmouse->m_pt;
      ScreenToClient(&pt);
      html::elemental * pelemental = get_html_data()->m_elemental.hit_test(pt);
      if(pelemental != NULL)
      {
         html::signal signal(pobj->m_psignal);
         signal.m_pdoccontainer = m_pcontainer;
         signal.m_psignal = pmouse;
         pelemental->OnMouseMove(&signal);
      }
   }

   void form_view::_001OnLButtonUp(ca::signal_object * pobj)
   {
      SCAST_PTR(::ca::message::mouse, pmouse, pobj);
      point pt;
      pt = pmouse->m_pt;
      ScreenToClient(&pt);
      html::elemental * pelemental = get_html_data()->m_elemental.hit_test(pt);
      if(m_pelementalLButtonDown != NULL
         && pelemental == m_pelementalLButtonDown)
      {
         html::signal signal(pobj->m_psignal);
         signal.m_pdoccontainer = m_pcontainer;
         signal.m_psignal = pmouse;
         m_pelementalLButtonDown->OnLButtonUp(&signal);
      }
   }

   html::document_container * form_view::calc_container()
   {
      if(m_pcontainer != NULL)
         return m_pcontainer;
      else
         return dynamic_cast < html::document_container * > (System.alloc(System.type_info < html::document_container > ()));
   }

   
   bool form_view::open_document(const char * pszPath)
   {
      return open_document(pszPath);
   }
   */

      /*

   string form_view::get_path()
   {
      return m_strPath;
   }


   bool form_view::open_document(const char * pszPath)
   {
      if(!m_pcontainer->open_document(pszPath))
         return false;
      m_strPath = pszPath;
      return true;
   }
   */

} // namespace userbase
