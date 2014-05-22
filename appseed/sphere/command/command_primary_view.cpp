#include "framework.h"


namespace command
{


   primary_view::primary_view(sp(::base::application) papp) :
      element(papp),
      ::user::interaction(papp),
      ::user::scroll_view(papp),
      ::colorertake5::base_editor(papp),
      ::data::data_listener(papp),
      ::user::edit_plain_text_view(papp)
   {

      m_iCompromised = 0;

      connect_update_cmd_ui("edit_copy", &primary_view::_001OnUpdateEditCopy);
      connect_command("edit_copy", &primary_view::_001OnEditCopy);
      connect_update_cmd_ui("edit_paste", &primary_view::_001OnUpdateEditPaste);
      connect_command("edit_paste", &primary_view::_001OnEditPaste);


   }

   void primary_view::on_update(sp(::user::impact) pSender, LPARAM lHint, ::object* phint)
   {

      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);
      UNREFERENCED_PARAMETER(phint);

   }

   void primary_view::install_message_handling(::message::dispatch * pinterface)
   {

      ::user::edit_plain_text_view::install_message_handling(pinterface);
	   IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &primary_view::_001OnContextMenu);

   }


   void primary_view::_001OnAfterChangeText(::action::context actioncontext)
   {
      string str;

      _001GetText(str);
      strsize iFind;
      strsize iFind2;

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
                  _001SetText(strNewText, ::action::source::sync());
                  str = strNewText;
                  m_iCompromised = m_ptree->m_iSelStart = m_ptree->m_iSelEnd = strNewText.get_length();
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
                     if(cregexp_util::match(stra, strLine, "(.+)\\s*segundos", true, 2) == 1)
                     {
                        calculator::parser parser(get_app());
                        calculator::element * pelement = parser.parse(stra[1]);
                        string strValue;
                        strValue.Format("%f", pelement->get_value());
                        string strMinFrac;
                        strMinFrac.Format("%f", pelement->get_value().mod() / 60.0);
                        string strMin;
                        strMin.Format("%d", ((int32_t)pelement->get_value().mod() / 60));
                        string strMinSec;
                        strMinSec.Format("%f", fmod(pelement->get_value().mod(), 60.0));
                        string strNewText = str + pelement->get_expression() + " segundos = " + strValue  + " segundos = " + strMinFrac + " minutos = " + strMin + " minutos e " + strMinSec + " segundos\n";
                        strNewText.replace("\r\n", "\n");
                        _001SetText(strNewText, ::action::source::sync());
                        str = strNewText;
                        m_iCompromised = m_ptree->m_iSelStart = m_ptree->m_iSelEnd = strNewText.get_length();
                        bOk = true;
                     }
                     else if(cregexp_util::match(stra, strLine, "(.+)\\s*dias", true, 2) == 1)
                     {
                        calculator::parser parser(get_app());
                        calculator::element * pelement = parser.parse(stra[1]);
                        string strValue;
                        strValue.Format("%f", pelement->get_value());
                        string strMinFrac;
                        strMinFrac.Format("%f", pelement->get_value().mod() / 60.0);
                        string strMin;
                        strMin.Format("%d", ((int32_t)pelement->get_value().mod() / 60));
                        string strMinSec;
                        strMinSec.Format("%f", fmod(pelement->get_value().mod(), 60.0));
                        string strNewText = str + pelement->get_expression() + " segundos = " + strValue  + " segundos = " + strMinFrac + " minutos = " + strMin + " minutos e " + strMinSec + " segundos\n";
                        strNewText.replace("\r\n", "\n");
                        _001SetText(strNewText, ::action::source::sync());
                        str = strNewText;
                        m_iCompromised = m_ptree->m_iSelStart = m_ptree->m_iSelEnd = strNewText.get_length();
                        Application.send_simple_command("winactionareaview::show_calendar(\""+ ::str::from((int32_t) pelement->get_value().mod()) +"\")", (void *) get_wnd()->get_os_data());
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

#ifdef WINDOWSEX

                  if(::ShellExecuteW(
                     NULL,
                     NULL,
                     ::str::international::utf8_to_unicode(strLine),
                     NULL,
                     NULL,
                     SW_SHOW))
                  {
                     string strNewText = str + "executing " + strLine  + "...";
                     strNewText.replace("\r\n", "\n");
                     _001SetText(strNewText, ::action::source::system());
                     m_iCompromised = m_ptree->m_iSelStart = m_ptree->m_iSelEnd = strNewText.get_length();
                  }

#else

                  throw todo(get_app());

#endif

               }
            }
         }


      }
   }

   void primary_view::_001OnUpdateEditCopy(signal_details * pobj)
   {
      SCAST_PTR(::base::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void primary_view::_001OnEditCopy(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      clipboard_copy();
   }

   void primary_view::_001OnUpdateEditPaste(signal_details * pobj)
   {
      SCAST_PTR(::base::cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }


   void primary_view::_001OnEditPaste(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      clipboard_paste();
   }


   void primary_view::_001OnContextMenu(signal_details * pobj)
   {

      track_popup_xml_matter_menu("command/popup_primary_verbing.xml", 0, pobj);

   }


} // namespace command


