// OptionsFoldersView.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsFoldersView.h"
#include "guibase/BaseViewFactory.h"
#include "resource.h"
#include "filemanager/FolderSelectionListView.h"


// OptionsFoldersView

IMPLEMENT_DYNCREATE(OptionsFoldersView, SimpleTabView)

OptionsFoldersView::OptionsFoldersView()
{
   _001SetVertical();


}

OptionsFoldersView::~OptionsFoldersView()
{
}

void OptionsFoldersView::_001InstallMessageHandling(igui::win::message::Dispatch * pinterface)
{
   SimpleTabView::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE         , this, this, &OptionsFoldersView::_001OnCreate);
   IGUI_WIN_ON_COMMAND(ID_EDIT_ADD     , this, this, &OptionsFoldersView::_001OnEditAdd);
   IGUI_WIN_ON_COMMAND(ID_EDIT_REMOVE  , this, this, &OptionsFoldersView::_001OnEditRemove);
}


// OptionsFoldersView message handlers
void OptionsFoldersView::_001OnCreate(gen::signal_object * pobj) 
{
   if(pobj->previous())
      return;


   AddTab(IDS_OPTIONSFOLDERS_TAB_SONG);
   AddTab(IDS_OPTIONSFOLDERS_TAB_IMAGE);
   AddTab(IDS_OPTIONSFOLDERS_TAB_AUTO_RECORD);

   _001SelectTab(0);

}

CWnd * OptionsFoldersView::_001GetTabWnd(int iTab)
{
   filemanager::Application * pfilemanagerapp = filemanager::GetApp();
   FolderSelectionListView * pview = NULL;
   if(!m_viewmap.Lookup((EOptionsFolders &) iTab, pview))
   {
      pview = dynamic_cast < FolderSelectionListView * > (BaseViewFactory::CreateView(
         0,
         RUNTIME_CLASS(FolderSelectionListView), 
         this, 
         GetDocument()));
      switch(iTab)
      {
      case OptionsFoldersSong:
         pview->Initialize(pfilemanagerapp->GetStdFileManagerTemplate(), "Song", VMSDATAKEY(SongDirectorySet));
         break;
      case OptionsFoldersImage:
         pview->Initialize(pfilemanagerapp->GetStdFileManagerTemplate(), "Image", VMSDATAKEY(ImageDirectorySet));
         break;
      case OptionsFoldersAutoRecord:
         pview->Initialize(pfilemanagerapp->GetStdFileManagerTemplate(), "AutoRecord", VMSDATAKEY(AutoRecordDirectory));
         break;
      }
      m_viewmap.SetAt((EOptionsFolders) iTab, pview);
   }
   return pview;
}

void OptionsFoldersView::_001OnEditAdd(gen::signal_object * pobj)
{
   FolderSelectionListView * pview = dynamic_cast < FolderSelectionListView * > (GetView());
   pview->FolderAdd();
}

void OptionsFoldersView::_001OnEditRemove(gen::signal_object * pobj)
{
   FolderSelectionListView * pview = dynamic_cast < FolderSelectionListView * > (GetView());
   pview->FolderRemove();
}

BaseView * OptionsFoldersView::GetView(void)
{
   return dynamic_cast < BaseView * > (_001GetTabWnd(_001GetSel()));
}
