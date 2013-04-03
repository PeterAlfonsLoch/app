#include "framework.h"


FileManagerInterface::FileManagerInterface()
{
   m_item.m_strPath.Empty();
}

FileManagerInterface::~FileManagerInterface()
{

}

bool FileManagerInterface::FileManagerBrowse(const ::fs::item & item)
{
   string strOldPath = m_item.m_strPath;
   try
   {
      if(&item != &m_item)
      {
         m_item.m_strPath        = item.m_strPath;
      }
      OnFileManagerBrowse();
   }
   catch(string & str)
   {
      if(str == "uifs:// You have not logged in!")
      {
         Application.simple_message_box(NULL, "You have not logged in! Cannot access your User Intelligent File System - uifs://");
         // assume can resume at least from this exception one time
         m_item.m_strPath = strOldPath;
         OnFileManagerBrowse();
      }
      return false;
   }
   return false;
}

bool FileManagerInterface::FileManagerBrowse(const char * lpcsz)
{

   ::fs::item item;

   item.m_strPath          = lpcsz;

   FileManagerBrowse(item);

   return false;

}

void FileManagerInterface::FileManagerOneLevelUp()
{

   if(get_item().m_strPath.is_empty())
      return;

   string strParent = get_fs_data()->eat_end_level(get_item().m_strPath, 1);

   FileManagerBrowse(strParent);

}

void FileManagerInterface::GetActiveViewSelection(::fs::item_array & itema)
{
   UNREFERENCED_PARAMETER(itema);
}


::fs::item & FileManagerInterface::get_item()
{
   return m_item;
}

critical_section * FileManagerInterface::GetItemIdListCriticalSection()
{
   return &m_csItemIdListAbsolute;
}

void FileManagerInterface::OnFileManagerBrowse()
{

      if(::ca::str::begins(m_item.m_strPath, "uifs://")
      || ::ca::str::begins(m_item.m_strPath, "fs://"))
      {
         data_set("InitialBrowsePath", ::ca::system::idEmpty, m_item.m_strPath);
      }
      else
      {

         id idMachine;

         #ifdef LINUX
            idMachine = "Linux";
         #elif defined(WINDOWSEX)
            idMachine = "Windows Desktop";
         #endif

         data_set("InitialBrowsePath", ::ca::system::idEmpty, "machinefs://");
         data_set("InitialBrowsePath", idMachine, m_item.m_strPath);

      }
   //get_filemanager_data()->OnFileManagerOpenFolder(get_item());
}

void FileManagerInterface::OpenSelectionProperties()
{
}

void FileManagerInterface::FileManagerSaveAs(::user::document_interface * pdocument)
{
   get_filemanager_data()->m_pdocumentSave = pdocument;
}

void FileManagerInterface::FileManagerSaveOK()
{
}

void FileManagerInterface::FileManagerSaveCancel()
{
}

::fs::data * FileManagerInterface::get_fs_data()
{
   return NULL;
}


string FileManagerInterface::calc_key(::database::id & idSection, ::database::id & id, ::database::id & idIndex)
{
   string str;
   str += idSection.get_id().str();
   str += ".";
   str += id.get_id().str();
   str += ".";
   str += idIndex.get_id().str();
   return str;
}
