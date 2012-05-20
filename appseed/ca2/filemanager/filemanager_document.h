#pragma once


namespace filemanager
{


   class CLASS_DECL_ca2 document :
      public ::fs::document,
      virtual public FileManagerInterface
   {
   public:


      sp(::filemanager::data)       m_spfilemanagerdata;



      document(::ca::application * papp);
      virtual ~document();


      file_manager_operation_document * get_operation_doc(bool bSwitch);


      virtual bool _001OnCommand(id id);
      virtual bool _001OnUpdateCmdUi(cmd_ui * pcmdui);

      virtual ::filemanager::data * get_filemanager_data();

      virtual ::fs::data * get_fs_data();

      virtual bool on_new_document();
   
      virtual bool HandleDefaultFileManagerItemCmdMsg(BaseCmdMsg * pcmdmsg, ::fs::item_array & itema);

      virtual void GetActiveViewSelection(::fs::item_array & itema);

      void PopViews();
      void CreateViews();
      void OpenFolder(::fs::item & item);
      void Initialize(bool bMakeVisible);
      DECL_GEN_SIGNAL(_001OnLevelUp)
      DECL_GEN_SIGNAL(_001OnUpdateLevelUp)
      DECL_GEN_SIGNAL(_001OnAddLocation)
      DECL_GEN_SIGNAL(_001OnUpdateAddLocation)
      DECL_GEN_SIGNAL(_001OnReplaceText)
      DECL_GEN_SIGNAL(_001OnUpdateReplaceText)
      DECL_GEN_SIGNAL(_001OnEditPaste)
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste)
      DECL_GEN_SIGNAL(_001OnFileSaveAs)
      DECL_GEN_SIGNAL(_001OnUpdateFileSaveAs)
      virtual void OnFileManagerBrowse();
      virtual void OpenSelectionProperties();
   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void FileManagerSaveAs(::user::document_interface * pdocument);

      bool set_filemanager_data(::filemanager::data * pdata);


   };


} // namespace filemanager

