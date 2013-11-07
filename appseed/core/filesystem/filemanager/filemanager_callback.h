#pragma once

#ifdef WINDOWS
#include <shlobj.h>
#endif


namespace filemanager
{


   class list_data;

   class CLASS_DECL_CORE callback :
      virtual public request_interface
   {
   public:


      callback();
      virtual ~callback();


      virtual void on_request(sp(::create_context) pcreatecontext);


      virtual void OnFileManagerOpenContextMenuFolder(::filemanager::list_data * pdata, sp(::fs::item)  item, stringa & straCommand, stringa & straCommandTitle);
      virtual void OnFileManagerOpenContextMenuFile(::filemanager::list_data * pdata, const ::fs::item_array & itema);
      virtual void OnFileManagerOpenContextMenu(::filemanager::list_data * pdata);
      virtual void OnFileManagerOpenFolder(::filemanager::list_data * pdata, sp(::fs::item)  item);
      virtual bool GetFileManagerItemCallback(::filemanager::list_data * pdata, id id, const ::fs::item_array & itema);
      virtual void OnFileManagerItemUpdate(::filemanager::list_data * pdata, cmd_ui * pcmdui, const ::fs::item_array & itema);
      virtual void OnFileManagerItemCommand(::filemanager::list_data * pdata, id pszId, const ::fs::item_array & itema);
      virtual void OnFileManagerInitializeFormPreData(::filemanager::list_data * pdata, id uiId, ::user::form * pform);


   };


} // namespace filemanager
