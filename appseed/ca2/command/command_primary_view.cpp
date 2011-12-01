#include "StdAfx.h"
#include <math.h>


namespace command
{



   primary_view::primary_view(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::user::interaction(papp), 
      ::userbase::edit_plain_text(papp), 
      ::userbase::view(papp),
      ::userbase::edit_plain_text_view(papp), 
      colorertake5::base_editor(papp),
      ::user::scroll_view(papp), 
      ::user::edit_plain_text(papp),
      ex1::tree(papp),
      ::ca::data_listener(papp)
   {
      m_iCompromised = 0;
      LOGFONT lf;
      memset(&lf, 0, sizeof(lf));
      strcpy(lf.lfFaceName, "Arial");
      lf.lfHeight = 16;

      m_font->CreateFontIndirect(&lf);
      connect_update_cmd_ui("edit_copy", &primary_view::_001OnUpdateEditCopy);
      connect_command("edit_copy", &primary_view::_001OnEditCopy);
      connect_update_cmd_ui("edit_paste", &primary_view::_001OnUpdateEditPaste);
      connect_command("edit_paste", &primary_view::_001OnEditPaste);
   }

   void primary_view::on_update(::view* pSender, LPARAM lHint, ::radix::object* phint) 
   {
      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);
   }

   void primary_view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::userbase::edit_plain_text_view::install_message_handling(pinterface);
	   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &primary_view::_001OnContextMenu);

   }


   void primary_view::_001OnAfterChangeText()
   {
      string str;

      _001GetText(str);
      int iFind;
      int iFind2;

      if((iFind = str.reverse_find('\n')) >= 0)
      {
         iFind2 = str.reverse_find('\n', iFind - 1);
         iFind2++;
         if(iFind > iFind2 && iFind2 >= m_iCompromised)
         {
            string strLine = str.Mid(iFind2, iFind - iFind2 - 1);
            if(strLine.has_char())
            {
               bool bOk = false;
               string strNewLine;
               try
               {
                  calculator::parser parser(get_app());
                  calculator::element * pelement = parser.parse(strLine);
                  string strValue;
                  strValue.Format("%f", pelement->get_value());
                  string strNewText = str + pelement->get_expression() + " = " + strValue  + "\n";
                  strNewText.replace("\r\n", "\n");
                  _001SetText(strNewText);
                  str = strNewText;
                  m_iCompromised = m_iSelStart = m_iSelEnd = strNewText.get_length();
                  bOk = true;
               }
               catch(const char * psz)
               {
                  TRACE("error %s", psz);
                  bOk = false;
               }

               try
               {
                  if(!bOk)
                  {
                     stringa stra;
                     if(PcreUtil::match(stra, strLine, "(.+)\\s*segundos", true, 2) == 1)
                     {
                        calculator::parser parser(get_app());
                        calculator::element * pelement = parser.parse(stra[1]);
                        string strValue;
                        strValue.Format("%f", pelement->get_value());
                        string strMinFrac;
                        strMinFrac.Format("%f", pelement->get_value().mod() / 60.0);
                        string strMin;
                        strMin.Format("%d", ((int)pelement->get_value().mod() / 60));
                        string strMinSec;
                        strMinSec.Format("%f", fmod(pelement->get_value().mod(), 60.0));
                        string strNewText = str + pelement->get_expression() + " segundos = " + strValue  + " segundos = " + strMinFrac + " minutos = " + strMin + " minutos e " + strMinSec + " segundos\n";
                        strNewText.replace("\r\n", "\n");
                        _001SetText(strNewText);
                        str = strNewText;
                        m_iCompromised = m_iSelStart = m_iSelEnd = strNewText.get_length();
                        bOk = true;
                     }
                     else if(PcreUtil::match(stra, strLine, "(.+)\\s*dias", true, 2) == 1)
                     {
                        calculator::parser parser(get_app());
                        calculator::element * pelement = parser.parse(stra[1]);
                        string strValue;
                        strValue.Format("%f", pelement->get_value());
                        string strMinFrac;
                        strMinFrac.Format("%f", pelement->get_value().mod() / 60.0);
                        string strMin;
                        strMin.Format("%d", ((int)pelement->get_value().mod() / 60));
                        string strMinSec;
                        strMinSec.Format("%f", fmod(pelement->get_value().mod(), 60.0));
                        string strNewText = str + pelement->get_expression() + " segundos = " + strValue  + " segundos = " + strMinFrac + " minutos = " + strMin + " minutos e " + strMinSec + " segundos\n";
                        strNewText.replace("\r\n", "\n");
                        _001SetText(strNewText);
                        str = strNewText;
                        m_iCompromised = m_iSelStart = m_iSelEnd = strNewText.get_length();
                        Application.send_simple_command("winactionareaview::show_calendar(\""+ gen::str::itoa((int) pelement->get_value().mod()) +"\")", get_wnd()->get_os_data());
                        bOk = true;
                     }
                  }
               }
               catch(const char * psz)
               {
                  TRACE("error %s", psz);
                  bOk = false;
               }
            
               if(!bOk)
               {
                  if(::ShellExecuteW(
                     NULL, 
                     NULL, 
                     gen::international::utf8_to_unicode(strLine),
                     NULL,
                     NULL,
                     SW_SHOW))
                  {
                     string strNewText = str + "executing " + strLine  + "...";
                     strNewText.replace("\r\n", "\n");
                     _001SetText(strNewText);
                     m_iCompromised = m_iSelStart = m_iSelEnd = strNewText.get_length();
                  }
               }
            }
         }
      

      }
   }

   void primary_view::_001OnUpdateEditCopy(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void primary_view::_001OnEditCopy(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      clipboard_copy();
   }

   void primary_view::_001OnUpdateEditPaste(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }


   void primary_view::_001OnEditPaste(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      clipboard_paste();
   }


   void primary_view::_001OnContextMenu(gen::signal_object * pobj) 
   {
      SCAST_PTR(::gen::message::context_menu, pcontextmenu, pobj)
      point point = pcontextmenu->GetPoint();

      ::userbase::menu menu(get_app());
      menu.LoadXmlMenu("command\\popup_primary_verbing.xml");
      ::userbase::menu menuPopup(get_app(), menu.GetSubMenu(0));
      menuPopup.TrackPopupMenu(0, point.x, point.y, GetParentFrame());

   }


} // namespace command