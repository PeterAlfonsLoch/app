#pragma once


class folder_list_view;


namespace filemanager
{


   class tree;


} // namespace filemanager



class CLASS_DECL_CORE folder_selection_list_view :
   virtual public ::user::split_view,
   virtual public ::filemanager::manager
{
public:


   ::filemanager::tree *    m_ptreeview;
   folder_list_view *                     m_plistview;
   sp(::filemanager::data)                  m_pdata;


   folder_selection_list_view(sp(::base::application) papp);
   ~folder_selection_list_view();


   virtual ::filemanager::data * get_filemanager_data();



   DECL_GEN_SIGNAL(_001OnAdd);
   DECL_GEN_SIGNAL(_001OnRemove);

   void install_message_handling(::message::dispatch * pinterface);

   void CreateViews();

   void Initialize(::filemanager::schema * ptemplate, const char * lpcszSection, ::database::id datakey, bool bRecursive);

   virtual void OnFileManagerBrowse(::action::context actioncontext);

   void FolderAdd();
   void FolderRemove();

};



