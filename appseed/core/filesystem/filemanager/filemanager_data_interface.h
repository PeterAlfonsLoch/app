#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE data_interface :
      virtual public ::object
   {
   public:
      

      sp(::filemanager::manager) m_pfilemanagerinterface;


      data_interface(sp(::base::application) papp);
      virtual ~data_interface();


      ::fs::item & GetFileManagerItem();

      virtual sp(::filemanager::manager) GetFileManager();
      virtual sp(::filemanager::document) GetFileManagerDoc();

      void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);


   };


} // namespace filemanager




