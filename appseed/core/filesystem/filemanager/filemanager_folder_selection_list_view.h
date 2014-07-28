#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE folder_selection_list_view:
      virtual public ::user::split_view,
      virtual public impact
   {
   public:


      sp(::user::tree)                          m_pusertree;
      sp(tree)                   m_ptree;
      folder_list_view *                        m_plistview;
      sp(data)                   m_pdata;


      folder_selection_list_view(sp(::base::application) papp);
      virtual ~folder_selection_list_view();


      virtual sp(data) get_filemanager_data();



      DECL_GEN_SIGNAL(_001OnAdd);
      DECL_GEN_SIGNAL(_001OnRemove);

      void install_message_handling(::message::dispatch * pinterface);

      void CreateViews();

      void Initialize(manager_template * ptemplate,const char * lpcszSection,::database::id datakey,bool bRecursive);

      virtual void OnFileManagerBrowse(::action::context actioncontext);

      void FolderAdd();
      void FolderRemove();

   };


} // namespace filemanager





