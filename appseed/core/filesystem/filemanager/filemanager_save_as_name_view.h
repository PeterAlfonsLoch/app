#pragma once


class CLASS_DECL_CORE FileManagerSaveAsView :
   virtual public ::user::edit_plain_text_view,
   virtual public ::filemanager::data_interface
{
public:


   FileManagerSaveAsView(sp(base_application) papp);


   virtual void _001OnAfterChangeText();


   bool m_bVoidSync;

   void _017Synchronize();
   void on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint);


};