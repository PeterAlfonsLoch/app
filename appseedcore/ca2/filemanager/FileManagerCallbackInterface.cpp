#include "StdAfx.h"

FileManagerCallbackInterface::FileManagerCallbackInterface()
{

}

FileManagerCallbackInterface::~FileManagerCallbackInterface()
{

}

void FileManagerCallbackInterface::OnFileManagerOpenContextMenuFolder(
   ::filemanager::data * pdata,
   ::fs::item & item)
{
   UNREFERENCED_PARAMETER(item);
   if(pdata->m_pmanager != NULL)
   {
      pdata->m_pmanager->OpenSelectionProperties();
   }
}

void FileManagerCallbackInterface::OnFileManagerOpenContextMenuFile(
   ::filemanager::data * pdata,
   ::fs::item_array & itema)
{
   UNREFERENCED_PARAMETER(itema);
   if(pdata->m_pmanager != NULL)
   {
      pdata->m_pmanager->OpenSelectionProperties();
   }
}

void FileManagerCallbackInterface::OnFileManagerOpenContextMenu(
   ::filemanager::data * pdata)
{
   UNREFERENCED_PARAMETER(pdata);
}

void FileManagerCallbackInterface::on_request(var & varFile, var & varQuery)
{
   ::ca::ca * pca = dynamic_cast < ::ca::ca * > (this);
   if(pca != NULL)
   {
      filemanager::launch_app_thread * pthread = new filemanager::launch_app_thread(pca->get_app());
      pthread->m_varFile = varFile;
      pthread->m_varQuery = varQuery;
      pthread->Begin();
   }
}

void FileManagerCallbackInterface::OnFileManagerOpenFolder(
   ::filemanager::data * pdata,
   ::fs::item & item)
{
   UNREFERENCED_PARAMETER(pdata);
   UNREFERENCED_PARAMETER(item);
}



void FileManagerCallbackInterface::OnFileManagerItemCommand(
   ::filemanager::data * pdata,
   id id,
   ::fs::item_array & itema)
{
   UNREFERENCED_PARAMETER(pdata);
   UNREFERENCED_PARAMETER(id);
   UNREFERENCED_PARAMETER(itema);
}

void FileManagerCallbackInterface::OnFileManagerItemUpdate(
   ::filemanager::data * pdata,
   cmd_ui * pcmdui,
   ::fs::item_array & itema)
{
   UNREFERENCED_PARAMETER(pdata);
   UNREFERENCED_PARAMETER(pcmdui);
   UNREFERENCED_PARAMETER(itema);
}


void FileManagerCallbackInterface::OnFileManagerInitializeFormPreData(
   ::filemanager::data * pdata, 
   id id, 
   ::user::form * pform)
{
   UNREFERENCED_PARAMETER(pdata);
   UNREFERENCED_PARAMETER(id);
   UNREFERENCED_PARAMETER(pform);
}


bool FileManagerCallbackInterface::GetFileManagerItemCallback(
      ::filemanager::data * pdata, 
      id id, 
      ::fs::item_array & itema)
{
   UNREFERENCED_PARAMETER(pdata);
   UNREFERENCED_PARAMETER(id);
   UNREFERENCED_PARAMETER(itema);
   return false;
}


namespace filemanager
{

   launch_app_thread::launch_app_thread(::ca::application * papp) : 
      ca(papp), 
      thread(papp) 
   {
   }


   bool launch_app_thread::initialize_instance() 
   { 
      return true;
   }

   int launch_app_thread::run()
   {
      if(m_itema.get_size() > 0)
      {
         ::ShellExecuteW(
               NULL, 
               NULL, 
               gen::international::utf8_to_unicode(m_itema[0].m_strPath),
               NULL,
               gen::international::utf8_to_unicode(System.dir().name(m_itema[0].m_strPath)),
               SW_SHOWNORMAL);
      }
      return 0;
   }

} // namespace filemanager
