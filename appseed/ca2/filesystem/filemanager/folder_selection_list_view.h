#pragma once

class CLASS_DECL_ca2 folder_selection_list_view :
   virtual public BaseSplitView,
   virtual public FileManagerInterface
{
public:
   folder_selection_list_view(::ca::application * papp);
public:
   ~folder_selection_list_view(void);

   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnAfterCreate)


   DECL_GEN_SIGNAL(_001OnAdd)
   DECL_GEN_SIGNAL(_001OnRemove)

   void _001InstallMessageHandling(igui::win::message::Dispatch * pinterface);

   void CreateViews();

   void Initialize(FileManagerTemplate * ptemplate, const char * lpcszSection, data_id datakey);

   virtual void OnFileManagerBrowse();
public:
   void FolderAdd(void);
public:
   void FolderRemove(void);
};
