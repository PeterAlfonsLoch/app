#include "StdAfx.h"

syllomatter_list_view::syllomatter_list_view(::ca::application * papp) :
   ca(papp),
   ::user::interaction(papp),
   ::user::form(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp),
   ::user::list(papp),
   simple_list_view(papp),
   ::user::form_list(papp),
   ::userbase::form_list(papp),
   m_headerctrl(papp),
   m_updatethread(papp),
   m_committhread(papp)
{
   m_updatethread.m_plistview = this;
   m_committhread.m_plistview = this;
   m_pheaderctrl->SetBaseListCtrlInterface(this);

   m_dataid = "syllomatter_list_view";
   connect_command("add", &syllomatter_list_view::_001OnAdd);
   connect_update_cmd_ui("add", &syllomatter_list_view::_001OnUpdateAdd);
   connect_command("delete", &syllomatter_list_view::_001OnDelete);
   connect_update_cmd_ui("delete", &syllomatter_list_view::_001OnUpdateDelete);
   connect_command("revert", &syllomatter_list_view::_001OnRevert);
   connect_update_cmd_ui("revert", &syllomatter_list_view::_001OnUpdateRevert);
   connect_command("commit", &syllomatter_list_view::_001OnCommit);
   connect_update_cmd_ui("commit", &syllomatter_list_view::_001OnUpdateCommit);
}


syllomatter_list_view::~syllomatter_list_view()
{
}


void syllomatter_list_view::install_message_handling(::user::win::message::dispatch * pinterface)
{
   ::userbase::form_list::install_message_handling(pinterface);
   ::userbase::view::install_message_handling(pinterface);
   IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &syllomatter_list_view::_001OnCreate);
   IGUI_WIN_MSG_LINK(MessageGeneralEvent, pinterface, this, &syllomatter_list_view::_001OnGeneralEvent);
   IGUI_WIN_MSG_LINK(WM_USER + 1024, this, this, &syllomatter_list_view::_001OnVerisvnwellListMessage);
}

void syllomatter_list_view::_001OnCreate(gen::signal_object * pobj)
{
   pobj->previous();

   
}

void syllomatter_list_view::_001InsertColumns()
{
   ::user::list_column column;

   column.m_iWidth               = 16;
   column.m_iSubItem             = 2;
   column.m_sizeIcon.cx          = 16;
   column.m_sizeIcon.cy          = 16;
   column.m_iControl             = -1;
   column.m_bEditOnSecondClick   = false;
   column.m_pil                  = System.shellimageset().GetImageList16();
   _001AddColumn(column);


   column.m_iWidth               = 20;
   column.m_iSubItem             = 0;
   _001AddColumn(column);

   column.m_iWidth               = 700;
   column.m_iSubItem             = 1;
   _001AddColumn(column);
}

void syllomatter_list_view::_001GetItemImage(::user::list_item * pitem)
{
   if(pitem->m_iSubItem == 2)
   {
      if(m_rangeSelection.HasItem(pitem->m_iItem))
      {
         pitem->m_iImage = 1;
         pitem->m_bOk = true;
      }
      else
      {
         pitem->m_iImage = 0;
         pitem->m_bOk = true;
      }
   }
   else
   {
      ::userbase::form_list::_001GetItemImage(pitem);
   }
}



void syllomatter_list_view::_001GetItemText(::user::list_item * pitem)
{
   if(pitem->m_iSubItem == 0)
   {
      pitem->m_strText = m_straStatus[pitem->m_iItem];
   }
   else if(pitem->m_iSubItem == 1)
   {
      pitem->m_strText = m_stra[pitem->m_iItem];
   }
   pitem->m_bOk = true;
}


INT_PTR syllomatter_list_view::_001GetItemCount()
{
   return m_stra.get_size();
}

void syllomatter_list_view::_001OnGeneralEvent(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj)
   if(pbase->m_wparam == GeneralEventPosCreate1)
   {
      _001UpdateColumns();
   }
}

void syllomatter_list_view::Commit_(::fs::item_array & itema)
{
   m_itema = itema;
   m_stra.remove_all();
   m_straStatus.remove_all();
   _001OnUpdateItemCount();
   stringa straSep;
   stringa straSub;
   straSep.add("\r");
   straSep.add("\n");
   straSep.add("\r\n");
   for(int i = 0; i < itema.get_size(); i++)
   {
      m_stra.add(itema[i].m_strPath);
      m_straStatus.add("X");
      string strCmd = System.dir().module("svn\\svn status ") 
         + itema[i].m_strPath;
      string strOutput;
      strOutput = System.process().get_output(strCmd);
      stringa stra;
      stra.add_smallest_tokens(strOutput, straSep, true, FALSE);
      for(int j = 0; j < stra.get_size(); j++)
      {
         stringa stra2;
         stra2.add_tokens(stra[j], " ", false);
         m_stra.add(stra2[1]);
         m_straStatus.add(stra2[0]);
         if(stra2[0] == "?" && System.dir().is(stra2[1]))
         {
            straSub.remove_all();
            System.dir().rls(stra2[1], &straSub);
            for(int l = 0; l < straSub.get_size(); l++)
            {
               m_stra.add(straSub[l]);
               m_straStatus.add("?");
            }

         }
      }
  }
   base_array < sort::ARG_COMPARE_FUNCTION, sort::ARG_COMPARE_FUNCTION > comparefna;
   base_array < sort::ARG_SWAP_FUNCTION, sort::ARG_SWAP_FUNCTION > swapfna;
   base_array < void *, void * > comparearga;
   base_array < void *, void * > swaparga;
   comparefna.add(&syllomatter_list_view::CompareStatus);
   comparefna.add(&syllomatter_list_view::ComparePath);
   comparearga.add((void *) this);
   comparearga.add((void *) this);
   swapfna.add(&syllomatter_list_view::Commit_Swap);
   swaparga.add((void *) this);
   ::sort::QuickSort(m_stra.get_size(), comparefna, swapfna, comparearga, swaparga);
   _001OnUpdateItemCount();
}


void syllomatter_list_view::Commit_Swap(LPVOID lparg, index dwa, index dwb)
{
   syllomatter_list_view * plist = (syllomatter_list_view *) lparg;
   string stra = plist->m_stra[dwa];
   plist->m_stra[dwa] = plist->m_stra[dwb];
   plist->m_stra[dwb] = stra;
   stra = plist->m_straStatus[dwa];
   plist->m_straStatus[dwa] = plist->m_straStatus[dwb];
   plist->m_straStatus[dwb] = stra;
}


index syllomatter_list_view::CompareStatus(LPVOID lparg, index dwa, index dwb)
{
   syllomatter_list_view * plist = (syllomatter_list_view *) lparg;
   return StatusSortWeight(plist->m_straStatus[dwa]) - StatusSortWeight(plist->m_straStatus[dwb]);
}


index syllomatter_list_view::StatusSortWeight(string & strStatus)
{
   if(strStatus == "M")
      return 1;
   else if(strStatus == "A")
      return 2;
   else if(strStatus == "D")
      return 3;
   else if(strStatus == "?")
      return 4;
   else if(strStatus == " ") // Title 1
      return -1;
   else
      return 5;
}

index syllomatter_list_view::ComparePath(LPVOID lparg, index dwa, index dwb)
{
   syllomatter_list_view * plist = (syllomatter_list_view *) lparg;
   return plist->m_stra[dwa].Compare(plist->m_stra[dwb]);
}

void syllomatter_list_view::_001OnAdd(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   Range range;
   _001GetSelection(range);
   for(int i = 0; i < range.get_item_count(); i++)
   {
      for(int iItem = range.ItemAt(i).GetLBound(); iItem <= range.ItemAt(i).GetUBound(); iItem++)
      {
         if(m_straStatus[iItem] == "?")
         {
            gen::process process;
            process.create_child_process(System.dir().module("svn\\svn add ") +
               m_stra[iItem], false);
            process.wait_until_exit();
         }
      }
   }
   Commit_(m_itema);
}

void syllomatter_list_view::_001OnUpdateAdd(gen::signal_object * pobj)
{
   Range range;
   _001GetSelection(range);
   bool bEnable = false;
   for(int i = 0; i < range.get_item_count(); i++)
   {
      for(int iItem = range.ItemAt(i).GetLBound(); iItem <= range.ItemAt(i).GetUBound(); iItem++)
      {
         if(m_straStatus[iItem] == "?")
         {
            bEnable = true;
            break;
         }
      }
      if(bEnable)
         break;
   }
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(bEnable);
}

void syllomatter_list_view::_001OnDelete(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   Range range;
   _001GetSelection(range);
   for(int i = 0; i < range.get_item_count(); i++)
   {
      for(int iItem = range.ItemAt(i).GetLBound(); iItem <= range.ItemAt(i).GetUBound(); iItem++)
      {
         if(m_straStatus[iItem] == "!")
         {
            gen::process process;
            process.create_child_process(System.dir().module("svn\\svn delete ") +
               m_stra[iItem], false);
            process.wait_until_exit();
         }
      }
   }
   Commit_(m_itema);
}

void syllomatter_list_view::_001OnUpdateDelete(gen::signal_object * pobj)
{
   Range range;
   _001GetSelection(range);
   bool bEnable = false;
   for(int i = 0; i < range.get_item_count(); i++)
   {
      for(int iItem = range.ItemAt(i).GetLBound(); iItem <= range.ItemAt(i).GetUBound(); iItem++)
      {
         if(m_straStatus[iItem] == "!")
         {
            bEnable = true;
            break;
         }
      }
      if(bEnable)
         break;
   }
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(bEnable);
}

void syllomatter_list_view::_001OnRevert(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   Range range;
   _001GetSelection(range);
   for(int i = 0; i < range.get_item_count(); i++)
   {
      for(int iItem = range.ItemAt(i).GetLBound(); iItem <= range.ItemAt(i).GetUBound(); iItem++)
      {
         if(m_straStatus[iItem] == "M" || m_straStatus[iItem] == "A")
         {
            gen::process * pprocess = new gen::process;
            pprocess->create_child_process(System.dir().module("svn\\svn revert ") +
               m_stra[iItem], false);
            pprocess->wait_until_exit();
            delete pprocess;
         }
      }
   }
   Commit_(m_itema);
}

void syllomatter_list_view::_001OnUpdateRevert(gen::signal_object * pobj)
{
   Range range;
   _001GetSelection(range);
   bool bEnable = false;
   for(int i = 0; i < range.get_item_count(); i++)
   {
      for(int iItem = range.ItemAt(i).GetLBound(); iItem <= range.ItemAt(i).GetUBound(); iItem++)
      {
         if(m_straStatus[iItem] == "M" || m_straStatus[iItem] == "A" || m_straStatus[iItem] == "D")
         {
            bEnable = true;
            break;
         }
      }
      if(bEnable)
         break;
   }
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(bEnable);
}

syllomatter_list_view::commit_thread::commit_thread(::ca::application * papp) :
   ca(papp),
   thread(papp),
   simple_thread(papp)
{
}

int syllomatter_list_view::commit_thread::run()
{
   string strCmd = System.dir().module("svn\\svn commit ");
   string strExtraCommitMessage;
   m_plistview->m_psvnview->m_peditview->_001GetText(strExtraCommitMessage);
   if(strExtraCommitMessage .get_length() > 0)
   {
      strExtraCommitMessage = "\r\n" + strExtraCommitMessage + "\r\n";
   }
   string strTime;
   strTime = System.file().time_square();
   string strContents;
   gen::property_set headers;
   string strQuery;
   strQuery.Format("id=%d", m_plistview->m_ppaneview->m_pviewForm->m_iMessageId);
   System.http().download(
      "https://ca2passport.com/ca2api/commit_message?" + strQuery, 
      strTime, 
      NULL, // post
      headers,
      ((::fontopus::user *)&ApplicationUser)->m_phttpcookies, &ApplicationUser);
   string strFile = Application.file().as_string(strTime);
   strFile += strExtraCommitMessage;
   Application.file().put_contents(strTime, strFile);
   strCmd += "--file " + strTime;
   strCmd += " ";
   string strCommitMessage;
   strCommitMessage = "Changed file(s):\r\n";
   for(int i = 0; i < m_stra.get_size(); i++)
   {
      strCmd += m_stra[i];
      strCmd += " ";
      strCommitMessage += m_stra[i];
      strCommitMessage += "\r\n";
   }
   TRACE(strCmd);
   gen::process process;
   string strOutput;
   string strNow;
   string strRead;
   string strLine;
   int iRetry = -1;
   if(process.create_child_process(strCmd, true))
   {
      while(true)
      {
         strNow = process.read();
         strRead += strNow;
         strOutput += strNow;
         while(true)
         {
            int iFind = strRead.find("\r\n");
            if(iFind >= 0)
            {
               strLine = strRead.Mid(0, iFind);
               strRead = strRead.Mid(iFind + 2);
               m_plistview->m_stra.add(strLine);
               m_plistview->m_straStatus.add("");
               m_plistview->PostMessageA(WM_USER + 1024, 0, 0);
            }
            else
            {
               break;
            }
         }
         if(iRetry < 0)
         {
            if(process.has_exited())
            {
               iRetry  = 100;
            }
         }
         else
         {
            iRetry--;
            if(iRetry == 0)
               break;
         }
      }
   }
   strTime = System.file().time_square();
   headers.m_propertya.remove_all();
   strQuery.Format("commitid=%d&debug&explain", m_plistview->m_ppaneview->m_pviewForm->m_iMessageId);
   gen::property_set propertysetPost;
   propertysetPost["message"] = System.url().url_encode(strExtraCommitMessage + strCommitMessage);
   gen::property_set set;
   if(strOutput.find("Committed revision") > 0)
   {
      System.http().download(
         "https://ca2passport.com/ca2api/commit_message?" + strQuery, 
         strTime,
         propertysetPost,
         headers, 
         set,
         ((::fontopus::user *)&ApplicationUser)->m_phttpcookies,
         &ApplicationUser);
   }
   return 0;
}


void syllomatter_list_view::_001OnCommit(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   Range range;
   _001GetSelection(range);
   for(int i = 0; i < range.get_item_count(); i++)
   {
      for(int iItem = range.ItemAt(i).GetLBound(); iItem <= range.ItemAt(i).GetUBound(); iItem++)
      {
         if(m_straStatus[iItem] == "M" || m_straStatus[iItem] == "A" || m_straStatus[iItem] == "D")
         {
            m_committhread.m_stra.add(m_stra[iItem]);
         }
      }
   }
   m_committhread.Begin();
}

void syllomatter_list_view::_001OnUpdateCommit(gen::signal_object * pobj)
{
   Range range;
   _001GetSelection(range);
   bool bEnable = range.get_item_count() > 0;
   SCAST_PTR(base_cmd_ui, pcmdui, pobj)
   pcmdui->m_pcmdui->Enable(bEnable);
}




syllomatter_list_view::update_thread::update_thread(::ca::application * papp) :
   ca(papp),
   thread(papp),
   simple_thread(papp)
{
}

int syllomatter_list_view::update_thread::run()
{
   m_plistview->m_stra.remove_all();
   m_plistview->m_straStatus.remove_all();
   m_plistview->PostMessageA(WM_USER + 1024, 0, 0);
   stringa straSep;
   stringa straSub;
   straSep.add("\r");
   straSep.add("\n");
   straSep.add("\r\n");
   string strRead;
   string strLine;
   for(int i = 0; i < m_itema.get_size(); i++)
   {
      m_plistview->m_stra.add("Updating " +  m_itema[i].m_strPath + "...");
      m_plistview->m_straStatus.add(" ");
      m_plistview->PostMessageA(WM_USER + 1024, 0, 0);
      string strCmd = System.dir().module("svn\\svn update ") + m_itema[i].m_strPath;
      string strOutput;
      gen::process process;
      int iRetry = -1;
      if(process.create_child_process(strCmd, true))
      {
         while(true)
         {
            strRead += process.read();
            while(true)
            {
               int iFind = strRead.find("\r\n");
               if(iFind >= 0)
               {
                  strLine = strRead.Mid(0, iFind);
                  strRead = strRead.Mid(iFind + 2);
                  m_plistview->m_stra.add(strLine.Mid(4));
                  m_plistview->m_straStatus.add(strLine.Mid(0, 1));
                  m_plistview->PostMessageA(WM_USER + 1024, 0, 0);
               }
               else
               {
                  break;
               }
            }
            if(iRetry < 0)
            {
               if(process.has_exited())
               {
                  iRetry  = 100;
               }
            }
            else
            {
               iRetry--;
               if(iRetry == 0)
                  break;
            }
         }
      }
   }
   m_plistview->m_stra.add(strRead);
   m_plistview->m_straStatus.add("");
/*   base_array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > comparefna;
   base_array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > swapfna;
   base_array < void *, void * > comparearga;
   base_array < void *, void * > swaparga;
   comparefna.add(&syllomatter_list_view::CompareStatus);
   comparefna.add(&syllomatter_list_view::ComparePath);
   comparearga.add((void *) this);
   comparearga.add((void *) this);
   swapfna.add(&syllomatter_list_view::Commit_Swap);
   swaparga.add((void *) this);
   QuickSort(m_plistview->m_stra.get_size(), comparefna, swapfna, comparearga, swaparga);*/
   m_plistview->PostMessageA(WM_USER + 1024, 0, 0);
   return 0;
}

void syllomatter_list_view::Update(::fs::item_array & itema)
{
   m_updatethread.m_itema = itema;
   m_updatethread.Begin();
}



void syllomatter_list_view::_001GetItemColor(::user::list_item * pitem)
{
   if(m_straStatus[pitem->m_iItem] == "M")
   {
      pitem->m_cr = RGB(100, 150, 255);
      pitem->m_bOk = true;
   }
   else if(m_straStatus[pitem->m_iItem] == "A")
   {
      pitem->m_cr = RGB(235, 150, 255);
      pitem->m_bOk = true;
   }
   else if(m_straStatus[pitem->m_iItem] == "D")
   {
      pitem->m_cr = RGB(255, 100, 55);
      pitem->m_bOk = true;
   }
   else
   {
      return ::userbase::form_list::_001GetItemColor(pitem);
   }
}


void syllomatter_list_view::_001OnVerisvnwellListMessage(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   if(pbase->m_wparam == 0)
   {
      if(pbase->m_lparam == 0)
      {
         _001OnUpdateItemCount();
         _001EnsureVisible(_001GetItemCount() - 1);
      }
   }
}