#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE list_data :
      virtual public ::userfs::list_data
   {
   public:


      sp(::user::document_interface)      m_pdocumentSave;
      callback   *                        m_pfilemanager;
      sp(manager)                         m_pmanager;
      sp(manager)                         m_pmanagerMain;
      callback *                          m_pcallback;
      schema *                            m_pschema;
      bool                                m_bTransparentBackground;
      string                              m_strDISection;
      sp(::user::place_holder)            m_pholderFileList;
      sp(::user::interaction)             m_ptreeFileTreeMerge;
      bool                                m_bSetBergedgeTopicFile;

      string                              m_strToolBar;
      string                              m_strToolBarSave;

      id                                  m_id;


      int32_t                             m_iTemplate;
      int32_t                             m_iDocument;
      int32_t                             m_iIconSize;
      bool                                m_bListText;
      bool                                m_bListSelection;
      bool                                m_bFileSize;
      bool                                m_bPassBk;
      bool                                m_bIconView;


      list_data(sp(base_application) papp);
      virtual ~list_data();

      bool is_saving();

      void FileManagerBrowse(const char * lpcsz);
      void FileManagerBrowse(sp(::fs::item)  item);
      void OnFileManagerOpenContextMenuFolder(sp(::fs::item)  item, stringa & straCommand, stringa & straCommandTitle);
      void OnFileManagerOpenContextMenuFile(const ::fs::item_array & itema);
      void OnFileManagerOpenContextMenu();
      void OnFileManagerOpenFile(const ::fs::item_array & itema);
      void OnFileManagerOpenFolder(sp(::fs::item)  str);

      void OnFileManagerItemUpdate(cmd_ui * pcmdui, const ::fs::item_array & itema);
      void OnFileManagerItemCommand(const char * pszId, const ::fs::item_array & itema);


   };


} // namespace filemanager




