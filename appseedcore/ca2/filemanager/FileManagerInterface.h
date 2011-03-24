#pragma once

class ::filemanager::data;

class CLASS_DECL_ca FileManagerInterface :
   virtual public ::database::client
{
public:
   virtual ::filemanager::data * get_filemanager_data() = 0;
   ::critical_section * GetItemIdListCriticalSection();
   ::fs::item & get_item();

   virtual bool FileManagerBrowse(::fs::item & item);
   virtual bool FileManagerBrowse(const char * lpcsz);

   virtual void FileManagerOneLevelUp();
   virtual void OnFileManagerBrowse();
   virtual void OpenSelectionProperties();

   virtual void GetActiveViewSelection(::fs::item_array & itema);


   virtual void FileManagerSaveAs(document * pdocument);
   virtual void FileManagerSaveOK();
   virtual void FileManagerSaveCancel();

   FileManagerInterface();
   virtual ~FileManagerInterface();

   ::critical_section   m_csItemIdListAbsolute;
   ::fs::item      m_item;
   string               m_strTopic;
};
