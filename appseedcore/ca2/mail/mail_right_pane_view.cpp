#include "StdAfx.h"

namespace mail
{

   right_pane_view::right_pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      m_cfg(papp),
      place_holder_container(papp)
   {

      m_pcreateview        = this;
      m_pviewdataOld       = NULL;

      m_etranslucency      = TranslucencyPresent;

      m_pviewdata          = NULL;
      m_pviewdataOld       = NULL;

   }

   right_pane_view::~right_pane_view()
   {
   }

   #ifdef _DEBUG
   void right_pane_view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void right_pane_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   void right_pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);

//      SCAST_PTR(::user::win::message::create, pcreate, pobj)

      if(pobj->previous())
         return;

      SetTimer(3004, 184, NULL);

      System.m_prightpaneview = this;

      add_tab("texto", pane_text);
      add_tab("configuration", pane_configuration);

   }

   void right_pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      ::userbase::tab_view::on_update(pSender, lHint, pHint);
      if(lHint == document::hint_email_changed)
      {
         set_cur_tab_by_id(pane_text);
      }
   }

   void right_pane_view::on_show_view() 
   {
      ::userex::pane_tab_view::on_show_view();
      switch(get_view_id())
      {
      case pane_configuration:
         {
            m_cfg.on_show(get_document()->m_paccount->m_strEmail);
         }
         break;
      case pane_text:
         {
            m_pmailview->open_email();
         }
         break;
      }
   }

   BOOL right_pane_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

      return ::userbase::view::PreCreateWindow(cs);
   }

   void right_pane_view::_001OnShowWindow(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void right_pane_view::on_create_view(view_data * pviewdata)
   {
//      application * papp = dynamic_cast < application * > ((dynamic_cast < userbase::frame_window * > (GetParentFrame()))->get_app());
      switch(pviewdata->m_id)
      {
      case pane_configuration:
         {
            if(m_cfg.initialize(this))
            {
               pviewdata->m_pdoc = m_cfg.m_pdoc;
               pviewdata->m_pwnd = m_cfg.m_pview->GetParentFrame();
            }
         }
         break;
      case pane_text:
         {
            pviewdata->m_pdoc = get_document();
            pviewdata->m_pwnd = ::view::create_view(typeid(mail::view), get_document(), this, 2);
            m_pmailview = dynamic_cast < mail::view * > (pviewdata->m_pwnd);
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
      if(pviewdata->m_pwnd != NULL)
      {
         pviewdata->m_eflag.signalize(::user::create_view::view_data::flag_hide_all_others_on_show);
      }
   }



   void right_pane_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &right_pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , this, this, &right_pane_view::_001OnMenuMessage);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &right_pane_view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &right_pane_view::_001OnShowWindow);

   }

   void right_pane_view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 3004)
      {
         if(!GetTopLevelParent()->IsWindowVisible())
         {
         }
      }
   }

   document * right_pane_view::get_document()
   {
      return dynamic_cast < document * > (::userex::pane_tab_view::get_document());
   }



} // namespace mail