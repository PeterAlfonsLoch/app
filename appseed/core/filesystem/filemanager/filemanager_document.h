#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE document :
      virtual public ::userfs::document,
      virtual public ::filemanager::manager
   {
   public:


      sp(::filemanager::data)       m_spfilemanagerdata;



      document(sp(base_application) papp);
      virtual ~document();


      virtual void on_create(sp(::create_context) pcreatecontext);


      sp(file_manager_operation_document) get_operation_doc(bool bSwitch);


      virtual bool on_simple_action(id id);
      virtual bool on_simple_update(cmd_ui * pcmdui);

      virtual ::filemanager::data * get_filemanager_data();

      virtual ::fs::data * get_fs_data();

      virtual bool on_new_document();
   
      virtual bool HandleDefaultFileManagerItemCmdMsg(base_cmd_msg * pcmdmsg, ::fs::item_array & itema);

      virtual void GetActiveViewSelection(::fs::item_array & itema);

      void PopViews();
      void CreateViews();
      void OpenFolder(sp(::fs::item) item, ::action::context actioncontext);
      void Initialize(bool bMakeVisible);
      DECL_GEN_SIGNAL(_001OnLevelUp);
      DECL_GEN_SIGNAL(_001OnUpdateLevelUp);
      DECL_GEN_SIGNAL(_001OnAddLocation);
      DECL_GEN_SIGNAL(_001OnUpdateAddLocation);
      DECL_GEN_SIGNAL(_001OnReplaceText);
      DECL_GEN_SIGNAL(_001OnUpdateReplaceText);
      DECL_GEN_SIGNAL(_001OnEditPaste);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnFileSaveAs);
      DECL_GEN_SIGNAL(_001OnUpdateFileSaveAs);
      virtual void OnFileManagerBrowse(::action::context actioncontext);
      virtual void OpenSelectionProperties();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void FileManagerSaveAs(sp(::user::object) pdocument);

      bool set_filemanager_data(::filemanager::data * pdata);


   };


} // namespace filemanager

