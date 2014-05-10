#include "framework.h"
#include "filesystem/filemanager/filemanager_folder_selection_list_view.h"

namespace nature
{

   appearance_view::appearance_view(sp(::base::application) papp) :
      element(papp),
      ::user::tab(papp),

      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
      m_etranslucency      = TranslucencyPresent;
      _001SetVertical();
   }

   appearance_view::~appearance_view()
   {
   }

   void appearance_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &appearance_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &appearance_view::_001OnSize);
      connect_command("edit_add", &appearance_view::_001OnEditAdd);
      connect_command("edit_remove", &appearance_view::_001OnEditRemove);
   }

#ifdef DEBUG
   void appearance_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void appearance_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   void appearance_view::_001OnCreate(signal_details * pobj)
   {

      if(pobj->previous())
         return;

      add_tab("<string id='nature:appearance_view_image_folder'>image folder</string>", view_image_folder);

      set_cur_tab_by_id(view_image_folder);

   }


   void appearance_view::on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint)
   {
      
      UNREFERENCED_PARAMETER(pSender);
      
      UNREFERENCED_PARAMETER(lHint);

      if(pHint != NULL)
      {
         if(base_class < ::user::view_update_hint > :: bases(pHint))
         {

            ::user::view_update_hint * puh = dynamic_cast < ::user::view_update_hint * > (pHint);

            if(puh->m_ehint == ::user::view_update_hint::hint_open_document)
            {

               set_cur_tab_by_id(view_image_folder);

            }

         }

      }

   }


   void appearance_view::_001OnSize(signal_details * pobj)
   {
      if(pobj->previous())
         return;
   }

   bool appearance_view::pre_create_window(CREATESTRUCT& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return ::user::impact::pre_create_window(cs);
   }

   void appearance_view::on_show_view()
   {
      ::user::tab_view::on_show_view();
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
      ::filemanager::filemanager & filemanager = Session.filemanager();
      sp(folder_selection_list_view) pview;
      pview =  (::user::impact::create_view(
         System.type_info < folder_selection_list_view > (),
         get_document(),
         this,
         pcreatordata->m_id).m_p);
      switch(pcreatordata->m_id)
      {
      case view_image_folder:
         pview->Initialize(&filemanager.std(), "Image", "core.nature.ImageDirectorySet", true);
         break;
      }
      pview->connect_command("edit_add", &folder_selection_list_view::_001OnAdd);
      pview->connect_command("edit_remove", &folder_selection_list_view::_001OnRemove);
      pcreatordata->m_pdoc = pview->get_document();
      pcreatordata->m_pwnd = pview;
      pcreatordata->m_eflag.signalize(::user::view_creator_data::flag_hide_all_others_on_show);
   }

   void appearance_view::_001OnEditAdd(signal_details * pobj)
   {
      sp(folder_selection_list_view) pview =  (get_view_uie().m_p);
      pview->FolderAdd();
      pobj->m_bRet = true;
   }

   void appearance_view::_001OnEditRemove(signal_details * pobj)
   {
      sp(folder_selection_list_view) pview =  (get_view_uie().m_p);
      pview->FolderRemove();
      pobj->m_bRet = true;
   }

} // namespace nature
