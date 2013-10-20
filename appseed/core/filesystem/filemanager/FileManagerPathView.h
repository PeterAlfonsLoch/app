#pragma once


class CLASS_DECL_CORE FileManagerPathView :
   virtual public ::user::edit_plain_text_view,
   virtual public FileManagerViewInterface
{
public:

   bool m_bVoidSync;



   FileManagerPathView(sp(base_application) papp);

   
   virtual void _001OnAfterChangeText();


   void _017Synchronize();
   void on_update(sp(::user::view) pSender, LPARAM lHint, object* phint);


};




