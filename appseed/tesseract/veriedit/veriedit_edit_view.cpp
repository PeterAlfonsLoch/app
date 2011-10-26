#include "StdAfx.h"

namespace veriedit
{

   edit_view::edit_view(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::user::interaction(papp), 
      ::user::scroll_view(papp), 
      ::colorertake5::base_editor(papp),
      ::ca::data_listener(papp),
      ::ex1::tree(papp),
      ::user::edit_plain_text(papp),
      ::userbase::edit_plain_text(papp), 
      ::userbase::view(papp),
      ::userbase::edit_plain_text_view(papp)
   {
      m_bMultiLine = true;
      //m_bColorerTake5 = true;
      connect_update_cmd_ui("edit_undo", &edit_view::_001OnUpdateEditUndo);
      connect_command("edit_undo", &edit_view::_001OnEditUndo);
      connect_update_cmd_ui("edit_redo", &edit_view::_001OnUpdateEditRedo);
      connect_command("edit_redo", &edit_view::_001OnEditRedo);
      connect_update_cmd_ui("media_transfer", &edit_view::_001OnUpdateMediaTransfer);
      connect_command("media_transfer", &edit_view::_001OnMediaTransfer);


      LOGFONT lf;

      memset(&lf, 0, sizeof(lf));
      lf.lfHeight = 16;
      strcpy(lf.lfFaceName, "Courier New");
      
      m_font->CreateFontIndirect(&lf);


      //m_etranslucency = TranslucencyPresent;

   }

   edit_view::~edit_view()
   {
   }



   #ifdef _DEBUG
   void edit_view::assert_valid() const
   {
      ::userbase::edit_plain_text_view::assert_valid();
   }

   void edit_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::edit_plain_text_view::dump(dumpcontext);
   }
   #endif //_DEBUG

   void edit_view::on_update(::view * pSender, LPARAM lHint, ::radix::object * phint) 
   {
      ::userbase::edit_plain_text_view::on_update(pSender, lHint, phint);
      if(lHint == 1001)
      {
         _001RedrawWindow();
      }
      else if(lHint == 11)
      {
         m_pdata->SetFile(get_document()->m_file);
         _001OnUpdate();
         // todo colorer_select_type();
      }
      else if(lHint == 123)
      {
         ::ca::data::writing writing(m_pdata);
         m_pdata->SetFile(get_document()->m_file);
         // todo colorer_select_type();
         ::ca::graphics * pdc = GetDC();
         _001OnCalcLayout(pdc);
         ReleaseDC(pdc);
         _001LayoutScrollBars();
      }
      else if(lHint == 12345)
      {
         m_pdata->m_editfile.Save(get_document()->m_fileSave);
      }
      else if(lHint == 1234508)
      {
         CreateLineIndex();
         m_bGetTextNeedUpdate = true;
         RedrawWindow();
         ::ca::graphics * pdc = GetDC();
         _001OnCalcLayout(pdc);
         ReleaseDC(pdc);

         AfxBeginThread(get_app(), ThreadProcScrollSize, dynamic_cast < ::user::edit_plain_text * > (this));

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

   void edit_view::_001OnContextMenu(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::user::win::message::context_menu, pcontextmenu, pobj)
//      int iItem;
//      HRESULT hr;
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

   document * edit_view::get_document() const
   {
      return dynamic_cast < document * > (::userbase::edit_plain_text_view::get_document());
   }

   void edit_view::_001OnUpdateEditUndo(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.CanUndo());
   }

   void edit_view::_001OnUpdateEditRedo(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.GetRedoBranchCount() > 0);
   }

   void edit_view::_001OnEditUndo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Undo();
   }

   void edit_view::_001OnEditRedo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Redo();
   }
   void edit_view::_001OnAfterChangeText()
   {
      ::userbase::edit_plain_text_view::_001OnAfterChangeText();
      get_document()->set_modified_flag(TRUE);
   }

   void edit_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::edit_plain_text_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &edit_view::_001OnContextMenu);
   }

   void edit_view::_001OnUpdateMediaTransfer(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void edit_view::_001OnMediaTransfer(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }

} // namespace veriedit