#pragma once


class folder_list_view;


namespace filemanager
{


   class SimpleFolderTreeView;


} // namespace filemanager


class CLASS_DECL_ca2 folder_selection_list_view :
   virtual public ::userbase::split_view,
   virtual public FileManagerInterface
{
public:


   filemanager::SimpleFolderTreeView *    m_ptreeview;
   folder_list_view *                     m_plistview;
   sp(filemanager::data)                  m_pdata;


   folder_selection_list_view(::ca::application * papp);
   ~folder_selection_list_view(void);


   virtual filemanager::data * get_filemanager_data();



   DECL_GEN_SIGNAL(_001OnAdd)
   DECL_GEN_SIGNAL(_001OnRemove)

   void install_message_handling(::gen::message::dispatch * pinterface);

   void CreateViews();

   void Initialize(FileManagerTemplate * ptemplate, const char * lpcszSection, ::database::id datakey, bool bRecursive);

   virtual void OnFileManagerBrowse();

   void FolderAdd(void);
   void FolderRemove(void);

};



