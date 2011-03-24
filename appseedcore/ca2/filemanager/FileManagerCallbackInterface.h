#pragma once

#include <shlobj.h>


namespace filemanager
{

   class data;

} // namespace filemanager



class CLASS_DECL_ca FileManagerCallbackInterface :
   virtual public file_manager_interface,
   virtual public ex1::request_interface
{
public:

   
   FileManagerCallbackInterface();
   virtual ~FileManagerCallbackInterface();


   virtual void on_request(var & varFile, var & varRequest);


   virtual void OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, ::fs::item & item);
   virtual void OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, ::fs::item_array & itema);
   virtual void OnFileManagerOpenContextMenu(::filemanager::data * pdata);
   virtual void OnFileManagerOpenFolder(::filemanager::data * pdata, ::fs::item & item);
   virtual bool GetFileManagerItemCallback(::filemanager::data * pdata, id id, ::fs::item_array & itema);
   virtual void OnFileManagerItemUpdate(::filemanager::data * pdata, cmd_ui * pcmdui, ::fs::item_array & itema);
   virtual void OnFileManagerItemCommand(::filemanager::data * pdata, id pszId, ::fs::item_array & itema);
   virtual void OnFileManagerInitializeFormPreData(::filemanager::data * pdata, id uiId, ::user::form * pform);




};


namespace filemanager
{
   class launch_app_thread :
      public ::radix::thread
   {
   public:
      launch_app_thread(::ca::application * papp);

      bool initialize_instance();

      var m_varFile;
      var m_varQuery;
      ::fs::item_array m_itema;
      int run();
   };



} // namespace filemanager