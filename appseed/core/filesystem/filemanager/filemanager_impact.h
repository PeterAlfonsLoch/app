#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE impact :
      virtual public object
   {
   public:
      

      ::filemanager::manager *      m_pmanager;


      impact(sp(::base::application) papp);
      virtual ~impact();


      ::fs::item & GetFileManagerItem();

      virtual sp(::filemanager::manager)              get_filemanager_manager();
      virtual sp(::filemanager::manager_template)     get_filemanager_template();
      virtual sp(::filemanager::data)                 get_filemanager_data();

      void on_update(sp(::user::impact) pSender, LPARAM lHint, object* pHint);


   };


} // namespace filemanager




