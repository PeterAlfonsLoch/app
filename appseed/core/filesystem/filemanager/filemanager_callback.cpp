//#include "framework.h"


namespace filemanager
{


   callback::callback()
   {

   }

   callback::~callback()
   {

   }

   void callback::OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, sp(::fs::item)  item, stringa & straCommand, stringa & straCommandTitle, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(straCommand);
      UNREFERENCED_PARAMETER(straCommandTitle);
      UNREFERENCED_PARAMETER(actioncontext);
      if (pdata->m_pmanager != NULL)
      {
         pdata->m_pmanager->OpenSelectionProperties();
      }
   }

   void callback::OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::fs::item_array & itema, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(itema);
      UNREFERENCED_PARAMETER(actioncontext);
      if (pdata->m_pmanager != NULL)
      {
         pdata->m_pmanager->OpenSelectionProperties();
      }
   }

   void callback::OnFileManagerOpenContextMenu(::filemanager::data * pdata, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(actioncontext);
   }

   void callback::on_request(sp(::create) pcreatecontext)
   {

      Application.request_create(pcreatecontext);

   }

   void callback::OnFileManagerOpenFolder(::filemanager::data * pdata, sp(::fs::item)  item, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(item);
      UNREFERENCED_PARAMETER(actioncontext);
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



