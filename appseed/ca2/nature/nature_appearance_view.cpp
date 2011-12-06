#include "StdAfx.h"
#include "filemanager/filemanager_folder_selection_list_view.h"

namespace nature
{

   appearance_view::appearance_view(::ca::application * papp) :
      ca(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
      m_etranslucency      = TranslucencyPresent;
      _001SetVertical();
   }

   appearance_view::~appearance_view()
   {
   }

   void appearance_view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &appearance_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &appearance_view::_001OnSize);
      connect_command("edit_add", &appearance_view::_001OnEditAdd);
      connect_command("edit_remove", &appearance_view::_001OnEditRemove);
   }

#ifdef _DEBUG
   void appearance_view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void appearance_view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
#endif //_DEBUG

   void appearance_view::_001OnCreate(gen::signal_object * pobj) 
   {
      
      if(pobj->previous())
         return;

      add_tab("<string id='nature:appearance_view_image_folder'>image folder</string>", view_image_folder);

      set_cur_tab_by_id(view_image_folder);

   }


   void appearance_view::on_update(::view * pSender, LPARAM lHint, ::radix::object* pHint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      if(pHint != NULL)
      {
         if(base <view_update_hint> :: bases(pHint))
         {
            view_update_hint * puh = dynamic_cast < view_update_hint * > (pHint);
            if(puh->m_etype == view_update_hint::TypeOpenDocument)
            {
               set_cur_tab_by_id(view_image_folder);
            }
         }
      }
   }


   void appearance_view::_001OnSize(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;
   }

   BOOL appearance_view::PreCreateWindow(CREATESTRUCT& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

      return ::userbase::view::PreCreateWindow(cs);
   }

   void appearance_view::on_show_view()
   {
      ::userbase::tab_view::on_show_view();
      simple_child_frame * pframe = GetTypedParent < simple_child_frame > ();
      switch(get_view_id())
      {
      case view_image_folder:
         {
            pframe->LoadToolBar(0, "mplite\\toolbar_options_frame.xml");
         }
         break;
      default:
         ASSERT(FALSE);
         break;
      }
      
   }

   void appearance_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      filemanager::application & filemanagerapp = dynamic_cast < filemanager::application & > (System);
      folder_selection_list_view * pview;
      pview = dynamic_cast < folder_selection_list_view * > (::view::create_view(
         System.type_info < folder_selection_list_view > (), 
         get_document(),
         this,
         pcreatordata->m_id));
      switch(pcreatordata->m_id)
      {
      case view_image_folder:
         pview->Initialize(filemanagerapp.GetStdFileManagerTemplate(), "Image", "ca2_fontopus_votagus.nature.ImageDirectorySet", true);
         break;
      }
      pview->connect_command("edit_add", &folder_selection_list_view::_001OnAdd);
      pview->connect_command("edit_remove", &folder_selection_list_view::_001OnRemove);
      pcreatordata->m_pdoc = pview->get_document();
      pcreatordata->m_pwnd = pview;
      pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
   }

   void appearance_view::_001OnEditAdd(gen::signal_object * pobj)
   {
      folder_selection_list_view * pview = dynamic_cast < folder_selection_list_view * > (get_view_uie());
      pview->FolderAdd();
      pobj->m_bRet = true;
   }

   void appearance_view::_001OnEditRemove(gen::signal_object * pobj)
   {
      folder_selection_list_view * pview = dynamic_cast < folder_selection_list_view * > (get_view_uie());
      pview->FolderRemove();
      pobj->m_bRet = true;
   }

} // namespace nature