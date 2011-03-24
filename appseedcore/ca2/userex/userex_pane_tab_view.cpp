#include "StdAfx.h"

namespace userex
{

   pane_tab_view::pane_tab_view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::user::tab(papp),
      place_holder_container(papp)
   {
      m_pcreateview = this;
   }

   pane_tab_view::~pane_tab_view()
   {
   }

   ::user::interaction * pane_tab_view::get_view_uie()
   {
      return ::userbase::tab_view::get_view_uie();
   }

   id pane_tab_view::get_view_id()
   {
      return ::userbase::tab_view::get_view_id();
   }

   void pane_tab_view::GetTabClientRect(LPRECT lprect)
   {
      if(m_pviewdata == NULL
      || m_pviewdata->m_pwnd == NULL
      || m_pviewdata->m_iExtendOnParent == 0)
      {
         ::userbase::tab_view::GetTabClientRect(lprect);
      }
      else if(m_pviewdata->m_iExtendOnParent > 0)
      {
         int i = m_pviewdata->m_iExtendOnParent;
         ::user::interaction* pguie = m_pviewdata->m_pwnd;
         ::user::interaction* pguieNext = m_pviewdata->m_pwnd;
         for(; i > 0; i--)
         {
            pguieNext = pguie->GetParent();
            if(pguieNext == NULL || !pguieNext->IsWindow())
               break;
            pguie = pguieNext;
         }
         pguie->GetWindowRect(lprect);
         ScreenToClient(lprect);
      }
      else if(m_pviewdata->m_iExtendOnParent < 0)
      {
         ::user::interaction* pguie = m_pviewdata->m_pwnd;
         ::user::interaction* pguieNext = m_pviewdata->m_pwnd;
         user::LPWndArray wnda;
         while(true)
         {
            wnda.add(pguie);
            pguieNext = pguie->GetParent();
            if(pguieNext == NULL || dynamic_cast < ::ca::window * > (pguie->m_pimpl) != NULL)
               break;
            pguie = pguieNext;
         }
//         int i = max(0, wnda.get_size() + m_pviewdata->m_iExtendOnParent);
         pguie = wnda[wnda.get_size() + m_pviewdata->m_iExtendOnParent];
         pguie->GetWindowRect(lprect);
         ScreenToClient(lprect);
      }
   }


   void pane_tab_view::on_show_view()
   {
      ::userbase::tab_view::on_show_view();
      ::user::create_view::on_show_view();
   }

} // namespace userex