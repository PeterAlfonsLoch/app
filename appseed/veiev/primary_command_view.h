#pragma once

class CLASS_DECL_CA2_VEIEV primary_command_view :
   public ::userbase::edit_plain_text_view
{
public:
   // DECLARE_DYNCREATE(primary_command_view)

   DECL_GEN_SIGNAL(_001OnUpdateEditCopy)
   DECL_GEN_SIGNAL(_001OnEditCopy)
   DECL_GEN_SIGNAL(_001OnUpdateEditPaste)
   DECL_GEN_SIGNAL(_001OnEditPaste)
	DECL_GEN_SIGNAL(_001OnContextMenu)

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);


   primary_command_view(::ca::application * papp);
   virtual void _001OnAfterChangeText();
   void on_update(::view* pSender, LPARAM lHint, ::radix::object* phint);

   int m_iCompromised;
};