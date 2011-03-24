#pragma once

//#include "vmsguibase/SimpleTabView.h"

// OptionsFoldersView
class FolderSelectionListView;

enum EOptionsFolders
{
   OptionsFoldersSong,
   OptionsFoldersImage,
   OptionsFoldersAutoRecord,
};

class OptionsFoldersView :
   public SimpleTabView
{
	DECLARE_DYNCREATE(OptionsFoldersView)

public:
	OptionsFoldersView();
	virtual ~OptionsFoldersView();

   BaseMap <   EOptionsFolders, EOptionsFolders, 
               FolderSelectionListView *, FolderSelectionListView * >
               m_viewmap;

   virtual CWnd * _001GetTabWnd(int iTab);

protected:
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnEditAdd)
   DECL_GEN_SIGNAL(_001OnEditRemove)
public:
   BaseView * GetView(void);

   virtual void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);
};


