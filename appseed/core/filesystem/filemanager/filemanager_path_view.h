#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE path_view :
   virtual public ::user::edit_plain_text_view,
      virtual public  data_interface
   {
   public:

      bool m_bVoidSync;



       path_view(sp(base_application) papp);


      virtual void _001OnAfterChangeText();


      void _017Synchronize();
      void on_update(sp(::user::view) pSender, LPARAM lHint, object* phint);


   };




} // namespace filemanager




