#pragma once


class CLASS_DECL_CORE FileManagerSaveAsView :
   virtual public ::user::edit_plain_text_view,
   virtual public ::filemanager::data_interface
{
public:


   FileManagerSaveAsView(sp(::base::application) papp);


   virtual void _001OnAfterChangeText(::action::context actioncontext);


   bool m_bVoidSync;

   void _017Synchronize(::action::context actioncontext);
   void on_update(sp(::user::impact) pSender, LPARAM lHint, object* phint);


};