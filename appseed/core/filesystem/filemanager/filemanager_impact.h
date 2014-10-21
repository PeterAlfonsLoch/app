#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE impact :
      virtual public object
   {
   public:
      

      ::filemanager::manager *      m_pmanager;


      impact();
      virtual ~impact();


      ::fs::item & get_filemanager_item();

      virtual sp(::filemanager::manager)              get_filemanager_manager();
      virtual sp(::filemanager::manager_template)     get_filemanager_template();
      virtual sp(::filemanager::data)                 get_filemanager_data();

      void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);

      virtual void browse_sync(::action::context actioncontext);
      virtual void knowledge(const string & strPath, ::action::context actioncontext);


   };


} // namespace filemanager




