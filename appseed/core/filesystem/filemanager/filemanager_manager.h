#pragma once


namespace filemanager
{


   class list_data;



   class CLASS_DECL_CORE manager :
      virtual public ::database::client
   {
   public:


      ::critical_section      m_csItemIdListAbsolute;
      sp(::fs::item)          m_item;
      string                  m_strTopic;



      manager();
      virtual ~manager();



      virtual list_data * get_filemanager_data() = 0;
      ::critical_section * GetItemIdListCriticalSection();
      ::fs::item & get_item();

      virtual bool FileManagerBrowse(sp(::fs::item)  item);
      virtual bool FileManagerBrowse(const char * lpcsz);

      virtual void FileManagerOneLevelUp();
      virtual void OnFileManagerBrowse();
      virtual void OpenSelectionProperties();

      virtual void GetActiveViewSelection(::fs::item_array & itema);


      virtual void FileManagerSaveAs(sp(::user::document_interface) pdocument);
      virtual void FileManagerSaveOK();
      virtual void FileManagerSaveCancel();


      virtual ::fs::data * get_fs_data();


      string calc_key(::database::id & idSection, ::database::id & id, ::database::id & idIndex);

   };


} // namespace filemanager




