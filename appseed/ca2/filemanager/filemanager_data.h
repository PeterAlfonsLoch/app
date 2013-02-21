#pragma once


class FileManagerCallbackInterface;
class FileManagerInterface;


namespace fs
{


   class item;
   class item_array;


} // namespace fs


class FileManagerTemplate;
class CWStrArray;
class CWStr;


namespace filemanager
{


   class CLASS_DECL_ca2 data :
      public ::fs::tree_data,
      public ::fs::list_data
   {
   public:


      ::user::document_interface *     m_pdocumentSave;
      ::gen::file_manager_interface *  m_pfilemanager;
      FileManagerInterface *           m_pmanager;
      FileManagerInterface *           m_pmanagerMain;
      FileManagerCallbackInterface *   m_pcallback;
      FileManagerTemplate *            m_ptemplate;
      bool                             m_bTransparentBackground;
      string                           m_strDISection;
      ::user::place_holder *           m_pholderFileList;
      ::user::interaction *            m_ptreeFileTreeMerge;
      bool                             m_bSetBergedgeTopicFile;

      string                           m_strToolBar;
      string                           m_strToolBarSave;

      id                               m_id;



   //   UINT  m_uiToolBar;
   //   UINT  m_uiMenuBar;

      int32_t   m_iTemplate;
      int32_t   m_iDocument;
      int32_t   m_iIconSize;
      bool  m_bListText;
      bool  m_bListSelection;
      bool  m_bFileSize;
      bool  m_bPassBk;
      bool  m_bIconView;


      data(::ca::application * papp);
      virtual ~data();

      bool is_saving();

      void FileManagerBrowse(const char * lpcsz);
      void FileManagerBrowse(const ::fs::item & item);
      void OnFileManagerOpenContextMenuFolder(const ::fs::item & item, stringa & straCommand, stringa & straCommandTitle);
      void OnFileManagerOpenContextMenuFile(const ::fs::item_array & itema);
      void OnFileManagerOpenContextMenu();
      void OnFileManagerOpenFile(const ::fs::item_array & itema);
      void OnFileManagerOpenFolder(const ::fs::item & str);

      void OnFileManagerItemUpdate(cmd_ui * pcmdui, const ::fs::item_array & itema);
      void OnFileManagerItemCommand(const char * pszId, const ::fs::item_array & itema);


   };


} // namespace filemanager


