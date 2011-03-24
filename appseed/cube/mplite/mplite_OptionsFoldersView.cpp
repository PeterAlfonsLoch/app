#include "StdAfx.h"
#include "OptionsFoldersView.h"
#include "filemanager/filemanager_folder_selection_list_view.h"

namespace mplite
{

   OptionsFoldersView::OptionsFoldersView(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::user::tab(papp),
      ::userbase::view(papp),
      ::userbase::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {
      m_etranslucency      = TranslucencyPresent;
      _001SetVertical();
   }

   OptionsFoldersView::~OptionsFoldersView()
   {
   }

   void OptionsFoldersView::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::_001InstallMessageHandling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &OptionsFoldersView::_001OnCreate);
      connect_command("edit_add", &OptionsFoldersView::_001OnEditAdd);
      connect_command("edit_remove", &OptionsFoldersView::_001OnEditRemove);
   }


   // OptionsFoldersView message handlers
   void OptionsFoldersView::_001OnCreate(gen::signal_object * pobj) 
   {
      if(pobj->previous())
         return;

      add_tab("<string id='mplite:options_folders_tab_song'>Song</string>", OptionsFoldersSong);
      add_tab("<string id='mplite:options_folders_tab_image'>Image</string>", OptionsFoldersImage);
      add_tab("<string id='mplite:options_folders_tab_auto_record'>Auto Record</string>", OptionsFoldersAutoRecord);

      set_cur_tab_by_id(OptionsFoldersSong);
   }

   void OptionsFoldersView::on_create_view(view_data * pviewdata)
   {
      filemanager::application & filemanagerapp = System;
      folder_selection_list_view * pview;
      pview = dynamic_cast < folder_selection_list_view * > (create_view(
         &typeid(folder_selection_list_view), 
         get_document(),
         this,
         pviewdata->m_id));
      switch(pviewdata->m_id)
      {
      case OptionsFoldersSong:
         pview->Initialize(filemanagerapp.GetStdFileManagerTemplate(), "Song", "ca2_fontopus_votagus.mplite.SongDirectorySet", true);
         break;
      case OptionsFoldersImage:
         pview->Initialize(filemanagerapp.GetStdFileManagerTemplate(), "Image", "ca2_fontopus_votagus.nature.ImageDirectorySet", true);
         break;
      case OptionsFoldersAutoRecord:
         pview->Initialize(filemanagerapp.GetStdFileManagerTemplate(), "AutoRecord", "ca2_fontopus_votagus.mplite.AutoRecordDirectory", false);
         break;
      }
      pview->connect_command("edit_add", &folder_selection_list_view::_001OnAdd);
      pview->connect_command("edit_remove", &folder_selection_list_view::_001OnRemove);
      pviewdata->m_pdoc = pview->get_document();
      pviewdata->m_pwnd = pview;
      pviewdata->m_eflag.signalize(view_data::flag_hide_all_others_on_show);
   }

   void OptionsFoldersView::_001OnEditAdd(gen::signal_object * pobj)
   {
      folder_selection_list_view * pview = dynamic_cast < folder_selection_list_view * > (get_view_uie());
      pview->FolderAdd();
      pobj->m_bRet = true;
   }

   void OptionsFoldersView::_001OnEditRemove(gen::signal_object * pobj)
   {
      folder_selection_list_view * pview = dynamic_cast < folder_selection_list_view * > (get_view_uie());
      pview->FolderRemove();
      pobj->m_bRet = true;
   }


} // namespace mplite
