#include "StdAfx.h"
#include "view.h"
#include "document.h"

namespace devedge
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::userbase::edit_plain_text(papp), 
      ::userbase::edit_plain_text_view(papp), 
      ::user::interaction(papp), 
      ::userbase::view(papp),
      ::user::scroll_view(papp), 
      colorertake5::base_editor(papp),
      ::user::edit_plain_text(papp),
      m_scrollbarVert(papp),
      m_scrollbarHorz(papp),
      ex1::tree(papp),
      ::ca::data_listener(papp)
   {
      m_bMultiLine = true;
      m_bColorerTake5 = true;
      connect_update_cmd_ui("edit_undo", &view::_001OnUpdateEditUndo);
      connect_command("edit_undo", &view::_001OnEditUndo);
      connect_update_cmd_ui("edit_redo", &view::_001OnUpdateEditRedo);
      connect_command("edit_redo", &view::_001OnEditRedo);

      m_pscrollbarVert  = &m_scrollbarVert;
      m_pscrollbarHorz  = &m_scrollbarHorz;

      LOGFONT lf;

      memset(&lf, 0, sizeof(lf));
      lf.lfHeight = 16;
      strcpy(lf.lfFaceName, "Courier New");
      
      m_font->CreateFontIndirect(&lf);

   }

   view::~view()
   {
   }



   #ifdef _DEBUG
   void view::assert_valid() const
   {
      ::userbase::edit_plain_text_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::edit_plain_text_view::dump(dumpcontext);
   }
   #endif //_DEBUG

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object * phint) 
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
         ::ca::graphics * pdc = GetDC();
         _001OnCalcLayout(pdc);
         ReleaseDC(pdc);
         LayoutScrollBars();
         colorer_select_type();
      }
      else if(lHint == 123)
      {
         m_pdata->SetFile(get_document()->m_file);
         colorer_select_type();
         ::ca::graphics * pdc = GetDC();
         _001OnCalcLayout(pdc);
         ReleaseDC(pdc);
         LayoutScrollBars();
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

   void view::_001OnContextMenu(gen::signal_object * pobj) 
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

   document * view::get_document() const
   {
      return dynamic_cast < document * > (::userbase::edit_plain_text_view::get_document());
   }

   void view::_001OnUpdateEditUndo(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.CanUndo());
   }

   void view::_001OnUpdateEditRedo(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(m_pdata->m_editfile.GetRedoBranchCount() > 0);
   }

   void view::_001OnEditUndo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Undo();
   }

   void view::_001OnEditRedo(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Redo();
   }

   void view::_001OnAfterChangeText()
   {
      ::userbase::edit_plain_text_view::_001OnAfterChangeText();
      get_document()->set_modified_flag(TRUE);
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::edit_plain_text_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
   }

} // namespace devedge