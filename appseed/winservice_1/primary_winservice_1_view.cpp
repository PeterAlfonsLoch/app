#include "StdAfx.h"

// IMPLEMENT_DYNCREATE(primary_command_view, base_edit_plain_text_view)

primary_command_view::primary_command_view(::ca::application * papp) :
   ::ca::ca(papp),
   uie(papp), 
   base_edit_plain_text_view(papp), 
   ex1::scroll_view(papp), 
   ex1::edit_plain_text(papp)
{
   LOGFONT lf;
   memset(&lf, 0, sizeof(lf));
   strcpy(lf.lfFaceName, "Arial");
   lf.lfHeight = 16;

   m_font.CreateFontIndirect(&lf);
}

void primary_command_view::OnUpdate(BaseView* pSender, LPARAM lHint, base_object* phint) 
{
}



void primary_command_view::_001OnAfterChangeText()
{
   string str;

   _001GetText(str);
   int iFind;
   if((iFind = str.find("\r")) >= 0)
   {
      _001SetText("");
      str = str.Left(iFind);
      if(!str.is_empty())
      {
         ::ShellExecuteW(
            NULL, 
            NULL, 
            gen::international::utf8_to_unicode(str),
            NULL,
            NULL,
            SW_SHOW);
      }
   }
}