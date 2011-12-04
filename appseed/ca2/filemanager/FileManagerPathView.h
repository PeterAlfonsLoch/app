#pragma once

class CLASS_DECL_ca2 FileManagerPathView :
   virtual public ::userbase::edit_plain_text_view,
   virtual public FileManagerViewInterface
{
public:
   FileManagerPathView(::ca::application * papp);

   virtual void _001OnAfterChangeText();


   bool m_bVoidSync;

   void _017Synchronize();
   void on_update(::view * pSender, LPARAM lHint, ::radix::object* phint);
};