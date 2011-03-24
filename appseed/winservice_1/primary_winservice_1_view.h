#pragma once

class CLASS_DECL_CA2_WINSERVICE_1 primary_command_view :
   public base_edit_plain_text_view
{
public:
   // DECLARE_DYNCREATE(primary_command_view)
   primary_command_view(::ca::application * papp);
   virtual void _001OnAfterChangeText();
   void OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint);
};