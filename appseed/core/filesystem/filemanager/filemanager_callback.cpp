#include "framework.h"


namespace filemanager
{


   callback::callback()
   {

   }

   callback::~callback()
   {

   }

   void callback::OnFileManagerOpenContextMenuFolder(::filemanager::list_data * pdata, sp(::fs::item)  item, stringa & straCommand, stringa & straCommandTitle)
   {
      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(straCommand);
      UNREFERENCED_PARAMETER(straCommandTitle);
      if (pdata->m_pmanager != NULL)
      {
         pdata->m_pmanager->OpenSelectionProperties();
      }
   }

   void callback::OnFileManagerOpenContextMenuFile(::filemanager::list_data * pdata, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(itema);
      if (pdata->m_pmanager != NULL)
      {
         pdata->m_pmanager->OpenSelectionProperties();
      }
   }

   void callback::OnFileManagerOpenContextMenu(::filemanager::list_data * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
   }

   void callback::on_request(sp(::create_context) pcreatecontext)
   {

      Application.request_create(pcreatecontext);

   }

   void callback::OnFileManagerOpenFolder(::filemanager::list_data * pdata, sp(::fs::item)  item)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(item);
   }

   void callback::OnFileManagerItemCommand(::filemanager::list_data * pdata, id id, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(itema);
   }

   void callback::OnFileManagerItemUpdate(::filemanager::list_data * pdata, cmd_ui * pcmdui, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(pcmdui);
      UNREFERENCED_PARAMETER(itema);
   }


   void callback::OnFileManagerInitializeFormPreData(::filemanager::list_data * pdata, id id, ::user::form * pform)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(pform);
   }


   bool callback::GetFileManagerItemCallback(::filemanager::list_data * pdata, id id, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(itema);
      return false;
   }



} // namespace filemanager



