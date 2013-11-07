#pragma once


namespace filemanager
{


   class document;


   class CLASS_DECL_CORE data_interface
   {
   public:
      
      data_interface();
      virtual ~data_interface();
   
      sp(::filemanager::manager) m_pfilemanagerinterface;

      ::fs::item & GetFileManagerItem();

      virtual sp(::filemanager::manager) GetFileManager();
      virtual sp(::filemanager::document) GetFileManagerDoc();

      void on_update(sp(::user::view) pSender, LPARAM lHint, object* pHint);


   };


} // namespace filemanager




