#pragma once


class CLASS_DECL_ca2 FileManagerSaveAsView :
   virtual public ::user::edit_plain_text_view,
   virtual public FileManagerViewInterface
{
public:


   FileManagerSaveAsView(sp(::ca2::application) papp);


   virtual void _001OnAfterChangeText();


   bool m_bVoidSync;

   void _017Synchronize();
   void on_update(sp(::user::view) pSender, LPARAM lHint, ::ca2::object* phint);


};