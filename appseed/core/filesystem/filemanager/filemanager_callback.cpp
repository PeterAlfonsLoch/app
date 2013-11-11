#include "framework.h"


namespace filemanager
{


   callback::callback()
   {

   }

   callback::~callback()
   {

   }

   void callback::OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, sp(::fs::item)  item, stringa & straCommand, stringa & straCommandTitle)
   {
      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(straCommand);
      UNREFERENCED_PARAMETER(straCommandTitle);
      if (pdata->m_pmanager != NULL)
      {
         pdata->m_pmanager->OpenSelectionProperties();
      }
   }

   void callback::OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(itema);
      if (pdata->m_pmanager != NULL)
      {
         pdata->m_pmanager->OpenSelectionProperties();
      }
   }

   void callback::OnFileManagerOpenContextMenu(::filemanager::data * pdata)
   {
      UNREFERENCED_PARAMETER(pdata);
   }

   void callback::on_request(sp(::create_context) pcreatecontext)
   {

      Application.request_create(pcreatecontext);

   }

   void callback::OnFileManagerOpenFolder(::filemanager::data * pdata, sp(::fs::item)  item)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(item);
   }

   void callback::OnFileManagerItemCommand(::filemanager::data * pdata, id id, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(itema);
   }

   void callback::OnFileManagerItemUpdate(::filemanager::data * pdata, cmd_ui * pcmdui, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(pcmdui);
      UNREFERENCED_PARAMETER(itema);
   }


   void callback::OnFileManagerInitializeFormPreData(::filemanager::data * pdata, id id, ::user::form * pform)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(pform);
   }


   bool callback::GetFileManagerItemCallback(::filemanager::data * pdata, id id, const ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(itema);
      return false;
   }



} // namespace filemanager



