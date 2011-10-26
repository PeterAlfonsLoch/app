#include "StdAfx.h"
#include "whiteboard.h"
#include "http_thread.h"
#include "http_window.h"
#include "time.h"
#include "view.h"
#include "document.h"

#define DEFER_NOTIFY_TIMER_MILLIS (75000)

namespace whiteboard
{

   http_thread::http_thread(::ca::application * papp) :
      ca(papp),
      thread(papp)
   {
      // answering
   /*   WB_REGISTER_RECEIVER(
         wb::message_key(
            wb::MessageClassAnswerTicket,
            MessageHttpRequest),
            this,
         &http_thread::on_http_get)*/

      m_iTimerNotify = DEFER_NOTIFY_TIMER_MILLIS;
      m_bDeferNotify = false;
      m_bLogin = false;
   }

   http_thread::~http_thread()
   {
   }

   bool http_thread::initialize_instance()
   {
   //   initialize_ticket_message_receiver(this, MessageTicketHdl);

      m_pwnd = new http_window(get_app());
      
      m_pwnd->create(this);

      DeferNotify();
      
      m_pwnd->SetTimer(TimerDeferNotify, m_iTimerNotify, NULL);
      //m_pwnd->SetTimer(TimerUserHour, m_iTimerUserHour, NULL);
      
      
      return true;
   }

   int http_thread::exit_instance()
   {
      // TODO:  perform any per-thread cleanup here
      return thread::exit_instance();
   }


   void http_thread::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      IGUI_WIN_MSG_LINK(MessageCommand, pinterface, this, &http_thread::OnCommandMessage);
      IGUI_WIN_MSG_LINK(MessageTimer, pinterface, this, &http_thread::OnTimerMessage);
   }

    // BEGIN_MESSAGE_MAP(http_thread, thread)
   //{{AFX_MSG_MAP(http_thread)
   // NOTE - the ClassWizard will add and remove mapping macros here.
   //}}AFX_MSG_MAP
   //ON_THREAD_MESSAGE(MessageCommand, OnCommandMessage)
   //ON_THREAD_MESSAGE(MessageTimer, OnTimerMessage)
   //ON_IWINTHREAD_MSGTICKETHDL(MessageTicketHdl)
    // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // http_thread message handlers

   void http_thread::DeferNotify()
   {
      if(m_bDeferNotify)
         return;
      
      keeper<bool> keepDeferNotify(&m_bDeferNotify, true, false, true);
      
      char szBuffer[20];
      char szBufferPrivate[20];
      
      
      memset(szBuffer, 0, sizeof(szBuffer));
      memset(szBufferPrivate, 0, sizeof(szBufferPrivate));
      
      
      string strNick;
      
      System.data_get("Options", "Nick", strNick);
      
      
      class time time;
      string str;
      
      db_getGroupDateTime(str, strNick);
      
      if(str.get_length() == 19)
      {
         
         time.m_iYear = atoi(str.Mid(0, 4));
         time.m_iMonth = atoi(str.Mid(5, 2));
         time.m_iDay = atoi(str.Mid(8, 2));
         time.m_iHour = atoi(str.Mid(11, 2));
         time.m_iMinute = atoi(str.Mid(14, 2));
         time.m_iSecond = atoi(str.Mid(17, 2));
         
         OnTime(time, TimeGroup);
      }
      else
      {
         time.m_iYear = 0;
         time.m_iMonth = 0;
         time.m_iDay = 0;
         time.m_iHour = 0;
         time.m_iMinute = 0;
         time.m_iSecond = 0;
         
         OnTime(time, TimeGroup);
      }
      
      string strPrivate;
      
      db_getUserDateTime(strPrivate, strNick);
      if(strPrivate.get_length() == 19)
      {
         time.m_iYear = atoi(strPrivate.Mid(0, 4));
         time.m_iMonth = atoi(strPrivate.Mid(5, 2));
         time.m_iDay = atoi(strPrivate.Mid(8, 2));
         time.m_iHour = atoi(strPrivate.Mid(11, 2));
         time.m_iMinute = atoi(strPrivate.Mid(14, 2));
         time.m_iSecond = atoi(strPrivate.Mid(17, 2));
         
         OnTime(time, TimePrivate);
      }
      else
      {
         time.m_iYear = 0;
         time.m_iMonth = 0;
         time.m_iDay = 0;
         time.m_iHour = 0;
         time.m_iMinute = 0;
         time.m_iSecond = 0;
         
         OnTime(time, TimePrivate);
      }

      if(GetLastChangeTime(time))
      {
         OnTime(time, TimeLastChange);
      }
   }

   bool http_thread::db_getDate(string & str, const char * lpcszKey)
   {
      return GetQueryResult(str, "get_date", lpcszKey);
   }

   bool http_thread::db_getTime(string & str,  const char * lpcszKey)
   {
      return GetQueryResult(str, "get_time", lpcszKey);
   }

   bool http_thread::db_getDateTime(string & str, const char * lpcszKey)
   {
      string strGet;
      
      str.Empty();
      if(!db_getDate(strGet,lpcszKey))
         return false;
      str += strGet;
      str += " ";
      if(!db_getTime(strGet,  lpcszKey))
         return false;
      str += strGet;
      
      return true;
   }

   bool http_thread::db_getGroupDateTime(string & str,  const char * lpcszOp)
   {
      string strKey;
      //string strGroupId;
      //if(!db_getUserGroupId(strGroupId,  lpcszOp))
        // return false;
      strKey.Format("whiteboard.change.group.op(%s)", lpcszOp);
      return db_getDateTime(str,  strKey);
   }

   bool http_thread::db_getUserDateTime(string & str,  const char * lpcszOp)
   {
      string strKey;
      strKey.Format("whiteboard.change(%s)", lpcszOp);
      return db_getDateTime(str,  strKey);
   }


   /*bool http_thread::db_getUserGroupId(string & str,  const char * lpcszOp)
   {
      return GetQueryResult(str, "get_user_group_id", lpcszOp);
   }*/


   void http_thread::OnTimerMessage(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::base, pbase, pobj);
      UINT nIDEvent = pbase->m_wparam;
      if(nIDEvent == TimerDeferNotify)
      {
         DeferNotify();
      }
      else if(nIDEvent == TimerUserHour)
      {
         UserHourPulseEvent();
      }
   }

   void http_thread::OnTime(class time & time, e_time etime)
   {

      class time timeStored;
      if(Application.GetProfileTime(timeStored, etime))
      {
         if(time.m_iYear != timeStored.m_iYear
            || time.m_iMonth != timeStored.m_iMonth 
            || time.m_iDay != timeStored.m_iDay
            || time.m_iHour != timeStored.m_iHour
            || time.m_iMinute != timeStored.m_iMinute
            || time.m_iSecond != timeStored.m_iSecond)
         {
            Application.SetProfileTime(time, etime);
            OnDirty();
         }
      }
      else
      {
         Application.SetProfileTime(time, etime);
         OnDirty();
      }
   }

   /*void CWhiteboardView::SetPrivateTime(time & time)
   {
   if(m_timePrivate.m_iYear != -1)
   {
   if(time.m_iYear != m_timePrivate.m_iYear
   || time.m_iMonth != m_timePrivate.m_iMonth 
   || time.m_iDay != m_timePrivate.m_iDay
   || time.m_iHour != m_timePrivate.m_iHour
   || time.m_iMinute != m_timePrivate.m_iMinute
   || time.m_iSecond != m_timePrivate.m_iSecond)
   {
   m_timePrivateQuery = m_time;
   m_bPrivateDirty = true;
   OnDirty();
   }
   }
   m_timePrivate = time;

     }
     
       void CWhiteboardView::SetTime(time & time)
       {
       if(m_time.m_iYear != -1)
       {
       if(time.m_iYear != m_time.m_iYear
       || time.m_iMonth != m_time.m_iMonth 
       || time.m_iDay != m_time.m_iDay
       || time.m_iHour != m_time.m_iHour
       || time.m_iMinute != m_time.m_iMinute
       || time.m_iSecond != m_time.m_iSecond)
       {
       m_timeQuery = m_time;
       m_bDirty = true;
       OnDirty();
       }
       }
       m_time = time;
       
   }*/


   /*bool http_thread::IsDirty(e_time etimeKey)
   {
      class time time;
      System.GetProfileTime(time, etimeKey);
      class time timeLastView;
      System.GetProfileTime(timeLastView, TimeLastView);
      return timeLastView < time;
   }
   */
   void http_thread::ViewWhiteboard()
   {
      PostCommandMessage(CommandViewWhiteboard);
   }

   void http_thread::PostCommandMessage(ECommand ecommand)
   {
      PostThreadMessage(MessageCommand, ecommand, 0);
   }


   void http_thread::OnCommandMessage(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      /* xxx
      ECommand ecommand = (ECommand) wparam;
      switch(ecommand)
      {
      case CommandViewWhiteboard:
         OnViewWhiteboard();
         break;
      default:
         ASSERT(FALSE);
         break;
      }
      */
   }

   void http_thread::OnViewWhiteboard()
   {
   }



   /*bool http_thread::IsGeneralDirty()
   {
      return IsDirty(TimeGroup) || IsDirty(TimePrivate);
   }*/

   void http_thread::OnDirty()
   {
      m_pview->OnDirty();
   }

   bool http_thread::GetLastChangeTime(class time &timeMaxParam)
   {
   /*   bool bExQuery = false;
      POSITION pos = m_mapDirty.get_start_position();
      
      if(pos != NULL)
      {
         bExQuery = true;
         e_time etimeKey;
         e_time etimeValue;
         class time time;
         m_mapDirty.get_next_assoc(pos, etimeKey, etimeValue);
         System.GetProfileTime(timeMax, etimeKey);
         while(pos != NULL)
         {
            m_mapDirty.get_next_assoc(pos, etimeKey, etimeValue);
            System.GetProfileTime(time, etimeKey);
            timeMax.Max(timeMax, time);
         }
         m_mapDirty.remove_all();
      }*/

      class time time;
      class time timeMax;
      
      if(!Application.GetProfileTime(time, TimeGroup))
         return false;
      timeMax = time;

      if(!Application.GetProfileTime(time, TimePrivate))
         return false;
      timeMax.Max(timeMax, time);
      timeMaxParam = timeMax;

   /*   string str;
      //string strKey;

      string strNick;
      
      strNick
      data_get("Options", "Nick", strNick);

      
      //strKey.Format("whiteboard.lastchange.::fontopus::user(%s)", strNick);

      GetQueryResult(str, "get_user_last_change", strNick);
      
      if(str.get_length() >= 19)
      {
         
         time.m_iYear = atoi(str.Mid(0, 4));
         time.m_iMonth = atoi(str.Mid(5, 2));
         time.m_iDay = atoi(str.Mid(8, 2));
         time.m_iHour = atoi(str.Mid(11, 2));
         time.m_iMinute = atoi(str.Mid(14, 2));
         time.m_iSecond = atoi(str.Mid(17, 2));
         
      }*/
      

      return true;
   }

   bool http_thread::GetQueryResult(string &str, const char * lpcszQryTyp, const char * lpcszKey)
   {
      str.Empty();

      string strBaseUrl;
      GetBaseUrl(strBaseUrl);

      string strQry;
      strQry.Format("%s/%s", lpcszQryTyp, lpcszKey);

      string strUrl;
      strUrl   =    strBaseUrl;
      if(strUrl.Right(1) != "/")
      {
         strUrl   +=   "/";
      }

      strUrl   +=   strQry;

      str = Application.http().get(strUrl);

      string xxx;
      xxx =  str.Left(100);
      TRACE("http_thread::GetQueryResult %s %s %s\n", lpcszQryTyp, lpcszKey, xxx);

      return true;
   }

   void http_thread::GetBaseUrl(string &str)
   {
      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
      papp->GetSiteUrl(SiteNotifyUrl, str);
   }

   bool http_thread::Login()
   {
      throw not_implemented_exception();
     /* string strUrl;
      string strBaseUrl;

      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
      papp->GetSiteUrl(SiteLogin, strUrl);

      string strItem;

      string strUser;
      string strPassword;

      m_pview->get_document()->GetUserOp(strUser);
      m_pview->get_document()->GetUserPassword(strPassword);

      strItem.Format("::fontopus::user=%s&password=%s", strUser, strPassword);

      //CHttpFile * pfile = (CHttpFile *) m_session.OpenURL(strUrl, 1.
         //INTERNET_FLAG_TRANSFER_ASCII, 
         //strHeaders);//

      string strServerName;
      int nPort = 80;

      int iFind1 = strUrl.find("//");
      int iFind2 = strUrl.find("/", iFind1 + 2);
      strServerName = strUrl.Mid(iFind1 + 2, iFind2 - iFind1 - 2);
      

      string strGet;

      strGet = strUrl.Mid(iFind2);
      string strHeader;

      strHeader = "Content-Type: application/x-www-form-urlencoded\r\n";
      CHttpConnection* pserver = NULL;
      CHttpFile* pfile = NULL;

      try
      {
         pserver = m_session.GetHttpConnection(strServerName, nPort);
      }
      catch(...)
      {
         TRACE("Connect error");
         return false;
      }
      pfile = pserver->OpenRequest(CHttpConnection::HTTP_VERB_POST, strGet);
      spfile->AddRequestHeaders(strHeader);
      
      spfile->SendRequestEx(strItem.get_length());
      spfile->write_string(strItem);
      spfile->EndRequest();
      DWORD dwRet;
      spfile->QueryInfoStatusCode(dwRet);

      char szBuff[256];
      string str;
      if (dwRet == HTTP_STATUS_OK)
      {
          while(true)
          {
             UINT nRead = spfile->read(szBuff, 255);
             szBuff[nRead] = 0;
             str += szBuff;
             if(nRead <= 0)
                break;
             spfile->read(szBuff, 255);
          }
      }
      delete pfile;
      delete pserver;

   */
      /*if(pfile == NULL)
      {
         //TRACE("FAIL http_thread::GetQueryResult %s %s\n", lpcszQryTyp, lpcszKey);
         return false;
      }

      spfile->close();*/

      TRACE("http_thread::Login: ");
   //   string xxx = str;
     // while(xxx.get_length() > 0)
      {
       //  TRACE("%s \n", xxx.Left(100));
         //xxx = xxx.Mid(100);
      }
      TRACE("\n");

      return true;
   }

   bool http_thread::UserHourPulseEvent()
   {
      throw not_implemented_exception();
         /*
      string strUrl;
      string strBaseUrl;

      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&Application);
      papp->GetSiteUrl(SitePulseUserEvent, strUrl);

      string strItem;

      string strUser;
      string strPassword;

      m_pview->get_document()->GetUserOp(strUser);
      m_pview->get_document()->GetUserPassword(strPassword);

      string strStatus;
      if(m_pview->IsSessionLocked())
      {
         strStatus = "locked_session";
      }
      else
      {
         strStatus = "running_session";
      }

      strItem.Format("::fontopus::user=%s&password=%s&status=%s", strUser, strPassword, strStatus);

      //CHttpFile * pfile = (CHttpFile *) m_session.OpenURL(strUrl, 1.
         //INTERNET_FLAG_TRANSFER_ASCII, 
         //strHeaders);//

      string strServerName;
      int nPort = 80;

      int iFind1 = strUrl.find("//");
      int iFind2 = strUrl.find("/", iFind1 + 2);
      strServerName = strUrl.Mid(iFind1 + 2, iFind2 - iFind1 - 2);


      int iFind3 = strServerName.find(":");
      if(iFind3 > 0)
      {
         nPort = atoi(strServerName.Mid(iFind3 + 1));
         strServerName = strServerName.Left(iFind3);
      }
      

      string strGet;

      strGet = strUrl.Mid(iFind2);
      string strHeader;

      strHeader = "Content-Type: application/x-www-form-urlencoded\r\n";
      CHttpConnection* pserver = NULL;
      CHttpFile* pfile = NULL;
         char szBuff[256];
         string str;

      DWORD dwRet;
      try
      {
         pserver = m_session.GetHttpConnection(strServerName, nPort);
         pfile = pserver->OpenRequest(CHttpConnection::HTTP_VERB_POST, strGet);
         spfile->AddRequestHeaders(strHeader);
         
         spfile->SendRequestEx(strItem.get_length());
         spfile->write_string(strItem);
         spfile->EndRequest();
         spfile->QueryInfoStatusCode(dwRet);
         if (dwRet == HTTP_STATUS_OK)
         {
            while(true)
            {
               UINT nRead = spfile->read(szBuff, 255);
               szBuff[nRead] = 0;
               str += szBuff;
               if(nRead <= 0)
                  break;
               spfile->read(szBuff, 255);
            }
         }
         delete pfile;
         delete pserver;

      }
      catch(...)
      {
         TRACE("Connect error");
         return false;
      }


      /*if(pfile == NULL)
      {
         //TRACE("FAIL http_thread::GetQueryResult %s %s\n", lpcszQryTyp, lpcszKey);
         return false;
      }

      spfile->close();*/

   /*
      TRACE("http_thread::Login: ");
      string xxx = str;
      while(xxx.get_length() > 0)
      {
         TRACE("%s \n", xxx.Left(100));
         xxx = xxx.Mid(100);
      }
      TRACE("\n");
   */
      return true;
   }





   /*void http_thread::on_http_get(wb::message * pmessageParam)
   {
      wb::http::request_message * pmessage = dynamic_cast < wb::http::request_message * > (pmessageParam);
      if(pmessage == NULL)
         return;
      
      string str;

      str.Empty();

   /*   string strBaseUrl;
      GetBaseUrl(strBaseUrl);

      string strQry;
      strQry.Format("%s/%s", lpcszQryTyp, lpcszKey);*/

    /*  string strUrl;
      pmessage->get_request(strUrl);
      /*if(strUrl.Right(1) != "/")
      {
         strUrl   +=   "/";
      }*/

   //   strUrl = pmessage->str;

   /*   CHttpFile * pfile = (CHttpFile *) m_session.OpenURL(strUrl);

      if(pfile == NULL)
      {
         TRACE("FAIL http_thread::GetQueryResult %s\n", strUrl);
         return;
      }

      string strItem;

      while(spfile->read_string(strItem))
      {
         str += strItem;
         //str += "\n";
      }

      string xxx;
      xxx =  str.Left(100);
      TRACE("http_thread::GetQueryResult %s %s\n", strUrl, xxx);

      pmessage->set_answer(str);
      
      pmessage->post_answer();

   }
   */

   void http_thread::pre_translate_message(gen::signal_object * pobj)
   {
   //   tick_message_receive_relay(pMsg);

      return __super::pre_translate_message(pobj);
   }

   void http_thread::ProcessMessageFilter(int code, gen::signal_object * pobj)
   {
      return __super::ProcessMessageFilter(code, pobj);
   }

} // namespace whiteboard