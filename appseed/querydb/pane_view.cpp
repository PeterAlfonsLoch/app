#include "StdAfx.h"

namespace querydb
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_pviewcreator = this;
      m_pviewdataOld = NULL;

      m_etranslucency      = TranslucencyPresent;

      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;


      

   }

   pane_view::~pane_view()
   {
   }

   #ifdef _DEBUG
   void pane_view::assert_valid() const
   {
	   ::userbase::view::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
	   ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // pane_view message handlers

   void pane_view::_001OnCreate(gen::signal_object * pobj) 
   {
//      SCAST_PTR(::user::win::message::create, pcreate, pobj)
      if(pobj->previous())
         return;

      SetTimer(3004, 184, NULL);

      add_tab("sql://query1.sql", "sql://query1.sql");

      frame * pframe = dynamic_cast < frame *> (GetTypedParent < ::querydb::frame >());
      pframe->m_ppaneview = this;

      set_cur_tab_by_id("sql://query1.sql");



   }

   void pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      /*if(lHint == 0)
      {
                  frame * pframe = dynamic_cast < frame *> (GetTopLevelParent());
                  pframe->SetActiveView(this);
      }*/
      ::userbase::tab_view::on_update(pSender, lHint, pHint);
      if(pHint != NULL)
      {
         if(base < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint *) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeGetView))
            {
            }
            else if(puh->is_type_of(pane_view_update_hint::TypeSetView))
            {
               set_cur_tab_by_id(puh->m_eview);
            }
         }
      }
	      if(pHint != NULL)
      {
   	   if(base < pane_view_update_hint >::bases(pHint))
         {
            pane_view_update_hint * puh = (pane_view_update_hint * ) pHint;
            if(puh->is_type_of(pane_view_update_hint::TypeOnShowKaraoke))
            {
               (dynamic_cast < userbase::frame_window * > (GetTopLevelFrame()))->SetActiveView(this);
            }
            else if(puh->is_type_of(pane_view_update_hint::TypeOnShowView))
            {
               
//               int iTab;
   //            if(puh->m_eview == PaneViewContextMenu)
     //          {
       //           m_tab._001AddSel(0);
         //      }
   //            else
               {
               }
               
            }
         }
      }

   }

   void pane_view::on_show_view() 
   {
      ::userex::pane_tab_view::on_show_view();
      frame * pframe = dynamic_cast < frame *> (GetParentFrame());
      if(get_view_id() == querydb::PaneViewFileManager)
      {
      }
      else
      {
      }
      pframe->SetActiveView(dynamic_cast < ::view *  > (get_view_uie()));
   }

   BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;	

	   return ::userbase::view::PreCreateWindow(cs);
   }

   void pane_view::_001OnShowWindow(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      querydb::application * papp = dynamic_cast < querydb::application * > (get_app());
      if(pcreatordata->m_id.is_text())
      {
         string strSql(pcreatordata->m_id);
         if(gen::str::begins_eat_ci(strSql, "sql://"))
         {
            document * pdoc = dynamic_cast < document * > (papp->m_ptemplateSql->open_document_file(strSql, true, this));
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > (pview->GetParentFrame());
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                     pcreatordata->m_strTitle = System.file().name_(strSql);
                  }
               }
            }
            return;
         }
      }
      if(pcreatordata->m_pwnd != NULL)
      {
         pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
      }
   }



   void pane_view::_001OnMenuMessage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      set_cur_tab_by_id(m_pviewdataOld->m_id);
   }

   void pane_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);

	   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
	   //IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &pane_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , this, this, &pane_view::_001OnMenuMessage);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &pane_view::_001OnTimer);
      IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &pane_view::_001OnShowWindow);

   }

   void pane_view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 3004)
      {
         if(!GetTopLevelParent()->IsWindowVisible())
         {
            if(get_cur_tab_id() != querydb::PaneViewWinActionArea)
            {
               set_cur_tab_by_id(querydb::PaneViewWinActionArea);
            }
         }
      }
   }


   void pane_view::rotate()
   {
      querydb::EPaneView eviewNew;
      switch(get_view_id())
      {
      case querydb::PaneViewContextMenu:
         eviewNew = querydb::PaneViewWinActionArea;
         break;
      case querydb::PaneViewWinActionArea:
         eviewNew = querydb::PaneViewFileManager;
         break;
      case querydb::PaneViewFileManager:
         eviewNew = querydb::PaneViewContextMenu;
         break;
      default:
         eviewNew = querydb::PaneViewWinActionArea;
      }

      set_cur_tab_by_id(eviewNew);
   }

   void pane_view::request(gen::command_line * pline)
   {
      FileManagerCallbackInterface::request(pline);
      GetParentFrame()->ShowWindow(SW_HIDE);
   }


   void pane_view::check_3click_dir(const char * psz)
   {
      stringa straPath;
      System.dir().ls(psz, &straPath);
      stringa straRelative;
      straPath.remove_all();
      System.dir().rls(Application.dir().userquicklaunch(), &straPath, NULL, &straRelative);
      for(int i = 0; i < straPath.get_size(); i++)
      {
         string str = System.dir().path(psz, straRelative[i]);
         System.dir().mk(System.dir().name(str));
         ::CopyFile(straPath[i], str, TRUE);
      }
   }

} // namespace querydb