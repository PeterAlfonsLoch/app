#include "StdAfx.h"

namespace i2com
{

   im_edit_view::im_edit_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp), 
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::userbase::scroll_view(papp),
      ::userbase::form_view(papp),
      m_scrollbarVert(papp),
      m_scrollbarHorz(papp),
      user::form(papp),
      html_form(papp)
   {
      connect_update_cmd_ui("edit_undo", &im_edit_view::_001OnUpdateEditUndo);
      connect_command("edit_undo", &im_edit_view::_001OnEditUndo);
      connect_update_cmd_ui("edit_redo", &im_edit_view::_001OnUpdateEditRedo);
      connect_command("edit_redo", &im_edit_view::_001OnEditRedo);

      m_pscrollbarVert  = &m_scrollbarVert;
      m_pscrollbarHorz  = &m_scrollbarHorz;

      LOGFONT lf;

      memset(&lf, 0, sizeof(lf));
      lf.lfHeight = 16;
      strcpy(lf.lfFaceName, "Courier New");
      
   }

   im_edit_view::~im_edit_view()
   {
   }



   #ifdef _DEBUG
   void im_edit_view::assert_valid() const
   {
      ::html_form::assert_valid();
   }

   void im_edit_view::dump(dump_context & dumpcontext) const
   {
      ::html_form::dump(dumpcontext);
   }
   #endif //_DEBUG

   void im_edit_view::on_update(::view * pSender, LPARAM lHint, ::radix::object * phint) 
   {
      ::html_form::on_update(pSender, lHint, phint);
      if(lHint == 1001)
      {
         _001RedrawWindow();
      }
      /*xxx if(phint != NULL)
      {
         if(base < PaneViewUpdateHint >::bases(phint))
         {
            PaneViewUpdateHint * puh = (PaneViewUpdateHint * ) phint;
            if(puh->is_type_of(PaneViewUpdateHint::TypeOnBeforeShowView))
            {
               get_document()->on_save_document(get_document()->get_path_name());
            }
            else if(puh->is_type_of(PaneViewUpdateHint::TypeOnShowView))
            {
               get_document()->reload();
            }
         }
      }*/
      
   }

   void im_edit_view::_001OnContextMenu(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
//      int iItem;
  //    HRESULT hr;
      //point point = pmouse->m_pt;
      point point;
      System.get_cursor_pos(&point);
      class point ptClient = point;
      ClientToScreen(&point);
      //ScreenToClient(&ptClient);
      ::userbase::menu menu(get_app());
      ex1::text_file_sp spfile(get_app());

      string strModuleFolder;
      strModuleFolder = System.get_module_folder();

      if(!spfile->open(System.dir().path(strModuleFolder, "devedge_contextmenu.xml"), ::ex1::file::type_text | ::ex1::file::mode_read))
         return;

      string str;
      spfile->read_full_string(str);

      xml::node node(get_app());

      node.load(str);

      if (menu.LoadMenu(&node))
      {
         //::userbase::menu* pPopup = (::userbase::menu_item *) menu.GetSubMenu(0);
         //ASSERT(pPopup != NULL);
         userbase::frame_window * pframe = dynamic_cast < userbase::frame_window * > ( dynamic_cast < ::ca::window * > (GetParentFrame()));
         //pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
           // point.x, point.y,
            //(::ca::window *) pframe);
         menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
            point.x, point.y,
            pframe);
      }
   }

   document * im_edit_view::get_document() const
   {
      return dynamic_cast < document * > (::html_form::get_document());
   }

   void im_edit_view::_001OnUpdateEditUndo(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
//      pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.CanUndo());
   }

   void im_edit_view::_001OnUpdateEditRedo(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
//      pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.GetRedoBranchCount() > 0);
   }

   void im_edit_view::_001OnEditUndo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      Undo();
   }

   void im_edit_view::_001OnEditRedo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      Redo();
   }

   void im_edit_view::_001OnAfterChangeText()
   {
//      ::userbase::edit_plain_text_view::_001OnAfterChangeText();
   }

   void im_edit_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::html_form::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &im_edit_view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &im_edit_view::_001OnCreate);
   }

   void im_edit_view::_001OnCreate(gen::signal_object * pobj)
   {
      if(pobj->previous())
         return;

      get_html_data()->m_bEdit = true;

      get_html_data()->load("<span style=\"color: #008800;\"> </span>");
      layout();
   }

   void im_edit_view::_009OnChar(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::key, pkey, pobj)

      if(pkey->m_nChar == 's')
      {
         if(::GetKeyState(VK_CONTROL) & 0x80000000)
         {
            return;
         }
      }

//      bool bShift = (::GetKeyState(VK_SHIFT) & 0x80000000) != 0;
      
      if(pkey->m_nChar == VK_RETURN)
      {
         post();
         pobj->m_bRet = true;
      }
   }

   void im_edit_view::post()
   {
      string strText;
      _001GetText(strText);
      string strPath;
      strPath = "http://i2com.api.veriterse.net/post";
      strPath = System.url().set(strPath, "topic", "message");
      strPath = System.url().set(strPath, "sessid", ApplicationUser.m_strSessid);
      strPath = System.url().set(strPath, "recipient", m_pimview->m_strRecipient);
      gen::property_set post(get_app());
      gen::property_set headers(get_app());
      gen::property_set set(get_app());
      post["message"] = strText;
      string str;
      Application.http().get(strPath, str, post, headers, set);
      //m_pimview->m_pstreamview->post(str);
      TRACE0(str);
      _001SetText("<span style=\"color: #008800;\"> </span>");
   }


   bool im_edit_view::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_enter_key)
      {
         post();
         return true;
      }
      return html_form::BaseOnControlEvent(pevent);
   }


} // namespace i2com