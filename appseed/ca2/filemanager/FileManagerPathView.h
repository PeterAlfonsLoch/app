#pragma once


class CLASS_DECL_ca2 FileManagerPathView :
   virtual public ::userbase::edit_plain_text_view,
   virtual public FileManagerViewInterface
{
public:

   bool m_bVoidSync;



   FileManagerPathView(sp(::ca::application) papp);

   
   virtual void _001OnAfterChangeText();


   void _017Synchronize();
   void on_update(::view * pSender, LPARAM lHint, ::ca::object* phint);


};




