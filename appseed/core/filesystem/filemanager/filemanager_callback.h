#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE callback :
      virtual public ::object
   {
   public:


      callback();
      virtual ~callback();


      virtual void on_request(sp(::create) pcreatecontext);


      virtual void OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, sp(::fs::item)  item, stringa & straCommand, stringa & straCommandTitle, ::action::context actioncontext);
      virtual void OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::fs::item_array & itema, ::action::context actioncontext);
      virtual void OnFileManagerOpenContextMenu(::filemanager::data * pdata, ::action::context actioncontext);
      virtual void OnFileManagerOpenFolder(::filemanager::data * pdata, sp(::fs::item)  item, ::action::context actioncontext);
      virtual bool GetFileManagerItemCallback(::filemanager::data * pdata, id id, const ::fs::item_array & itema);
      virtual void OnFileManagerItemUpdate(::filemanager::data * pdata, cmd_ui * pcmdui, const ::fs::item_array & itema);
      virtual void OnFileManagerItemCommand(::filemanager::data * pdata, id pszId, const ::fs::item_array & itema);
      virtual void OnFileManagerInitializeFormPreData(::filemanager::data * pdata, id uiId, ::user::form * pform);


   };


} // namespace filemanager





