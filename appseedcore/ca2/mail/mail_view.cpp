#include "StdAfx.h"

namespace mail
{

   view::view(::ca::application * papp) :
      ca(papp),
      ::userbase::view(papp)
   {
      m_pdoc = NULL;
      m_puie = NULL;
   }

   view::~view()
   {
   }

   void view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::userbase::view::_001InstallMessageHandling(pinterface);
   }

   #ifdef _DEBUG
   void view::assert_valid() const
   {
      ::userbase::view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::userbase::view::dump(dumpcontext);
   }
   #endif //_DEBUG

   void view::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint) 
   {
      ::view::on_update(pSender, lHint, phint);
      if(lHint == document::hint_open_email)
      {
         open_email();
      }
   }

   document * view::get_document()
   {
      return dynamic_cast < document * > (::userbase::view::get_document());
   }

   void view::layout()
   {
      rect rectClient;
      GetClientRect(rectClient);
      if(m_puie != NULL)
      {
         m_puie->SetWindowPos(NULL, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW);
      }
   }

   void view::_001OnDraw(::ca::graphics * pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);
      //pdc->FillSolidRect(rectClient, RGB(255, 255, 255));
      ::view::_001OnDraw(pdc);
   }

   void view::open_email()
   {
      CSingleLock slDataset(&get_document()->m_paccount->m_pop3.m_csDataset, TRUE);
      string strId = get_document()->m_strOpenEmailId;
      get_document()->m_paccount->m_pop3.m_pdataset->query("select headers from inbox where id = '" + strId + "'");
      if(get_document()->m_paccount->m_pop3.m_pdataset->num_rows() <= 0)
         return;
      string strHeaders = get_document()->m_paccount->m_pop3.m_pdataset->FieldValueAt(0);
      get_document()->m_paccount->m_pop3.m_pdataset->query("select body from inbox where id = '" + strId + "'");
      string str = get_document()->m_paccount->m_pop3.m_pdataset->FieldValueAt(0);

      bool bMultipart = false;
      stringa straHeaders;
      straHeaders.add_tokens(strHeaders, "\r\n", TRUE);
      string strLine;
      string strKey;
      string strValue;
      string strKey2;
      string strValue2;
      string strItem;
      string strBoundary;
      int iPos;
      for(int i = 0; i < straHeaders.get_size(); i++)
      {
         strLine = straHeaders[i];
         iPos = strLine.find(":");
         if(iPos > 0)
         {
            strKey = strLine.Mid(0, iPos);
            strValue = strLine.Mid(iPos + 1);
            if(strKey.CompareNoCase("Content-type") == 0)
            {
               stringa straItems;
               straItems.add_tokens(strValue, ";", FALSE);
               for(int j = 0; j < straItems.get_size(); j++)
               {
                  int iPos2;
                  strItem = straItems[j];
                  iPos2 = strItem.find("=");
                  if(iPos2 > 0)
                  {
                     strKey2 = strItem.Mid(0, iPos2);
                     strKey2.trim();
                     strValue2 = strItem.Mid(iPos2 + 1);
                     if(strKey2.CompareNoCase("boundary") == 0)
                     {
                        strValue2.replace(" ", "");
                        strValue2.replace("\"", "");
                        strBoundary = "--" + strValue2;
                     }
                  }
                  if(strItem.find("multipart/") >= 0)
                  {
                     bMultipart = true;
                  }
               }
            }
         }
      }
      string strDoc = "<html><head></head><body>";
      string strLines;
      stringa straLines;
      stringa straSep;
      straSep.add("\r");
      straSep.add("\n");
      straSep.add("\r\n");
      straSep.add("\n\r");
      straLines.add_smallest_tokens(str, straSep, TRUE);
      bool bInMultipart = false;
      for(int i = 0; i < straLines.get_size(); i++)
      {
         if(bMultipart)
         {
            if(straLines[i] == strBoundary)
            {
               bInMultipart = true;
               while(straLines[i] != "" && i < straLines.get_size())
               {
                  i++;
               }
               continue;
            }
            if(bInMultipart)
            {
               strLines += "<span>";
               strLines += System.html().entities(straLines[i]);
               strLines += "</span>";
            }
         }
         else
         {
            strLines += "<span style=\"font-family: Courier New, fixed-width;\">";
            strLines += System.html().entities(straLines[i]);
            strLines += "</span>";
            strLines += "<br>";
         }
      }
      strDoc += strLines;
      strDoc += "</body>";
      if(m_pdoc != NULL)
      {
         m_pdoc->on_close_document();
      }
      m_pdoc = System.create_form(this, this);
      m_pdoc->get_html_data()->load(strDoc);
      m_puie = m_pdoc->get_html_data()->get_frame();
      html_view_update_hint uh;
      uh.m_etype = html_view_update_hint::type_document_complete;
      uh.m_strUrl = strId;
      m_pdoc->update_all_views(NULL, 0, &uh);
      layout();
   }

} // namespace mail