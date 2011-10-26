#include "StdAfx.h"

namespace veriedit
{

   pane_view::pane_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {

      m_pfilemanagerdoc    = NULL;
      m_pfilemanagerdocFs  = NULL;

      m_etranslucency      = TranslucencyPresent;

      get_data()->m_bVertical = true;

      get_data()->m_matchanyRestore.add(new ::ex1::match::prefix("veriedit:"));

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

      set_tab("menu", veriedit::PaneViewContextMenu);
      set_tab("Plain Text Media", veriedit::PaneViewEdit);
      set_tab("File Manager", "file_manager");
      set_tab("Printer", "printer", false);


      veriedit::application * papp = dynamic_cast < veriedit::application * > (get_app());
      papp->m_ppaneview = this;
   }


   void pane_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(pHint);

   }

   void pane_view::on_show_view()
   {
      ::userex::pane_tab_view::on_show_view();
      if(m_pviewdata->m_id ==  veriedit::PaneViewEdit
      || (m_pviewdata->m_id.is_text() && gen::str::begins_ci(m_pviewdata->m_id, "veriedit://")))
      {
         (dynamic_cast < veriedit::main_frame * > (GetParentFrame()))->LoadToolBar("veriedit/edit_toolbar.xml");
         show_tab_by_id("printer");
      }
      else if(m_pviewdata->m_id == "printer")
      {
         ::simple_printer_list_view * pview = get_document()->get_typed_view < ::simple_printer_list_view >();
         pview->m_pview = m_pviewdataOld->m_pdoc->get_view();
      }
      else
      {
         show_tab_by_id("printer", false);
      }
      if(m_pviewdata->m_id !=  veriedit::PaneViewFileManager)
      {
         if(m_pfilemanagerdoc != NULL)
         {
            m_pfilemanagerdoc->get_filemanager_data()->m_pdocumentSave = NULL;
         }
      }
      if(m_pviewdata->m_id !=  veriedit::PaneViewFsManager)
      {
         if(m_pfilemanagerdocFs != NULL)
         {
            m_pfilemanagerdocFs->get_filemanager_data()->m_pdocumentSave = NULL;
         }
      }
   }


   BOOL pane_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

      return ::userbase::view::PreCreateWindow(cs);
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      veriedit::application * papp = dynamic_cast < veriedit::application * > (get_app());
      if(pcreatordata->m_id.is_text())
      {
         string strPath(pcreatordata->m_id);
         if(gen::str::begins_eat_ci(strPath, "veriedit://"))
         {
            document * pdoc = dynamic_cast < document * > (papp->m_ptemplateEdit->open_document_file(strPath, true, pcreatordata->m_pholder));
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
                     pcreatordata->m_strTitle = System.file().name_(strPath);
                  }
               }
            }
            return;
         }
      }
      if(pcreatordata->m_id == "printer")
      {
         {

            ::view * pview = ::view::create_view < ::simple_printer_list_view > (get_document(), pcreatordata->m_pholder);
            if(pview != NULL)
            {
//               ::userbase::menu_list_view * pmenuview = (::userbase::menu_list_view *) pview;
               pcreatordata->m_pdoc = get_document();
               pcreatordata->m_pwnd = pview;
            }
         }
         return;
      }
      switch(pcreatordata->m_id)
      {
      case veriedit::PaneViewContextMenu:
         /*{
            devedgeFrontDoc * pdoc = (devedgeFrontDoc *) (dynamic_cast < veriedit::application * > (((userbase::frame_window *) GetParentFrame())->m_papp))->m_ptemplateFront->open_document_file("http://localhost:10011/");
            if(pdoc != NULL)
            {
               POSITION pos = pdoc->get_view_count();
               ::userbase::view * pview = pdoc->get_view(pos);
               if(pview != NULL)
               {
                  userbase::frame_window * pframe = (userbase::frame_window *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;


                  }
               }
            }
         }*/
            break;
      case veriedit::PaneViewEdit:
         {
            document * pdoc = dynamic_cast < document * > (papp->m_ptemplateEdit->open_document_file(NULL, true, pcreatordata->m_pholder));
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  frame_window * pframe = (frame_window *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;
                  }
               }
            }
         }
         break;
      /*case veriedit::PaneViewFileManager:
         {
            ::filemanager::document * pdoc = papp->GetStdFileManagerTemplate()->OpenChild(papp, false, true, pcreatordata->m_pholder);
            m_pfilemanagerdoc = pdoc;
            if(pdoc != NULL)
            {
               ::view * pview = pdoc->get_view();
               if(pview != NULL)
               {
                  frame_window * pframe = (frame_window *) pview->GetParentFrame();
                  if(pframe != NULL)
                  {
                     pcreatordata->m_pdoc = pdoc;
                     pcreatordata->m_pwnd = pframe;

                     pdoc->Initialize(true);
                  }
               }
            }
         }
         break;*/


      default:
         break;
      }
      ::userex::pane_tab_view::on_create_view(pcreatordata);
   }


   void pane_view::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
   }

   document * pane_view::get_veriedit_document(const char * pszUrl)
   {
      veriedit::application * papp = dynamic_cast < veriedit::application * > (get_app());
      count count = papp->m_ptemplateEdit->get_document_count();
      string strPath(pszUrl);
      gen::str::begins_eat_ci(strPath, "veriedit://");
      for(index i = 0; i < count; i++)
      {
         document * pdoc = dynamic_cast < document * > (papp->m_ptemplateEdit->get_document(i));
         if(pdoc != NULL && pdoc->get_path_name().CompareNoCase(strPath) == 0)
         {
            return pdoc;
         }
      }
      return NULL;
   }

   void pane_view::get_opened_documents(stringa & stra)
   {
      var_array vara;
      get_restore_tab(vara);
      stra = vara;
   }

} // namespace veriedit