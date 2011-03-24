#include "StdAfx.h"

namespace whiteboard
{

   html_view::html_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::userbase::scroll_view(papp),
      ::user::form(papp),
      ::userbase::form_view(papp),
      html_form(papp),
      ::html_view(papp)
   {
      m_bSetTargetFrameName = false;
      m_estate = state_initial;

      connect_command("view_user_hour", &html_view::_001OnViewUserHour);
      connect_update_cmd_ui("view_user_hour", &html_view::_001OnUpdateViewUserHour);
      connect_command("view_bookmark", &html_view::_001OnViewBookmark);
      connect_update_cmd_ui("view_bookmark", &html_view::_001OnUpdateViewBookmark);
      connect_command("view_annotate", &html_view::_001OnViewAnnotate);
      connect_update_cmd_ui("view_annotate", &html_view::_001OnUpdateViewAnnotate);
   }

   html_view::~html_view()
   {
   }

   /*void html_view::DoDataExchange(CDataExchange* pDX)
   //{
   //   html_view::DoDataExchange(pDX);
      //{{AFX_DATA_MAP(html_view)
         // NOTE: the ClassWizard will add DDX and DDV calls here
      //}}AFX_DATA_MAP
   }


   // // BEGIN_MESSAGE_MAP(html_view, html_view)
      //{{AFX_MSG_MAP(html_view)
   /*   ON_WM_ERASEBKGND()
      ON_COMMAND(ID_VIEW_GO_FORWARD, OnViewGoForward)
      ON_UPDATE_COMMAND_UI(ID_VIEW_GO_FORWARD, OnUpdateViewGoForward)
      ON_COMMAND(ID_VIEW_GO_UP_HOME, OnViewGoUpHome)
      ON_COMMAND(ID_VIEW_GO_WB_HOME, OnViewGoWbHome)
      ON_COMMAND(ID_VIEW_GO_BACK, OnViewGoBack)
      ON_UPDATE_COMMAND_UI(ID_VIEW_GO_BACK, OnUpdateViewGoBack)
      ON_COMMAND(ID_VIEW_IN_IE, OnViewInIe)
      ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
      ON_WM_CREATE()
      ON_COMMAND(ID_VIEW_GO_CALENDAR, OnViewGoCalendar)
      ON_COMMAND(ID_VIEW_GO_USERHOUR, OnViewGoUserHour)
      ON_MESSAGE(MessageOnAfterDocumentComplete, OnAfterDocumentComplete)
      //}}AFX_MSG_MAP
      ON_MESSAGE(WM_APP + 12, OnExMouseMessage)
   //   ON_MESSAGE(MessageHttpGet, OnMessageHttpGet)
   ON_WM_SIZE()*/
   // // END_MESSAGE_MAP()

   /////////////////////////////////////////////////////////////////////////////
   // html_view diagnostics

   #ifdef _DEBUG
   void html_view::assert_valid() const
   {
      ::html_view::assert_valid();
   }

   void html_view::dump(dump_context & dumpcontext) const
   {
      ::html_view::dump(dumpcontext);
   }

   #endif //_DEBUG

   document* html_view::get_document() // non-debug version is inline
   {
      ASSERT(base < document >::bases(::view::get_document()));
      return dynamic_cast < document * > (::view::get_document());
   }


   /////////////////////////////////////////////////////////////////////////////
   // html_view message handlers

   BOOL html_view::OnEraseBkgnd(::ca::graphics * pgraphics) 
   {
      // TODO: add your message handler code here and/or call default
      return TRUE;
      //return html_view::OnEraseBkgnd(pgraphics);
   }

   void html_view::OnViewGoForward() 
   {
   //   GoForward();
   }

   void html_view::OnUpdateViewGoForward(cmd_ui * pcmdui) 
   {
      pcmdui->Enable();
   }

   void html_view::OnViewGoUpHome() 
   {
      document * pdoc = (document *) get_document();
      pdoc->update_all_views(NULL, 321124, NULL);
   }

   void html_view::OnViewGoWbHome() 
   {
      document * pdoc = (document *) get_document();
      pdoc->update_all_views(NULL, 321123, NULL);
   }



   void html_view::OnViewGoBack() 
   {
   //   GoBack();
   }

   void html_view::OnUpdateViewGoBack(cmd_ui * pcmdui) 
   {
      pcmdui->Enable();
      
   }

   void html_view::OnViewInIe() 
   {
      OpenNewInIe(this->GetLocationURL());
      
   }

   void html_view::OpenNewInIe(const char * lpcsz)
   {
      win::registry reg;
      string str;
      string str2;
      string strCommand;
      win::registry::Key key;
      if(key.OpenKey(HKEY_CLASSES_ROOT, ".html", false))
      {
         if(reg.RegQueryValue(key.m_hkey, "", str))
         {
            if(key.OpenKey(HKEY_CLASSES_ROOT, ".html\\shell\\opennew\\command", false))
            {
               string str;
               if(reg.RegQueryValue(HKEY_CLASSES_ROOT, str, str2))
               {
                  string strCommand(str2);
                  strCommand.replace("%1", lpcsz);
                  WinExec(strCommand,SW_SHOW);
               }
            }
            else
            {
               if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
               {
                  str += "\\shell\\opennew\\command";
                  if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
                  {
                     if(reg.RegQueryValue(key.m_hkey, "", str2))
                     {
                        string strCommand(str2);
                        strCommand.replace("%1", lpcsz);
                        WinExec(strCommand,SW_SHOW);
                     }
                  }
               }
            }
         }
      }
   }

   void html_view::OnViewRefresh() 
   {
      Refresh2(3);
   }

   void html_view::on_document_complete(const char * lpszURL) 
   {
      string str;
      str = m_strTargetFrameName;
      if(gen::str::begins_eat(str, "WhiteboardSpecialFrameFor:MRTS"))
      {
   //      html_view::OnDocumentComplete(lpszURL);
         return;
      }


      string strTitle;
   /*   LPDISPATCH lpdispDocument = GetHtmlDocument();

      if(lpdispDocument != NULL)
      {
         CComPtr<IHTMLDocument2> spHtml2;
         lpdispDocument->QueryInterface(IID_IHTMLDocument2, (void **) &spHtml2);

         if(spHtml2 != NULL)
         {
            BSTR bstrTitle;
            spHtml2->get_title(&bstrTitle);
            strTitle = bstrTitle;
         }
      }
      
      if(strTitle.get_length() > 0)
      {
         strTitle += " - ";
      }
      */

      strTitle = get_document()->get_html_data()->m_strTitle;

      if(strTitle.get_length() > 0)
      {
         strTitle += " - ";
      }

      strTitle += "Whiteboard Desktop System";



      get_document()->GetRootView()->m_strHtmlTitle = strTitle;
      get_document()->update_all_views(NULL, document::HintUpdateFrameTitle);
      //GetParentFrame()->on_update_frame_title(false);

   //   html_view::OnDocumentComplete(lpszURL);
      PostMessage(MessageOnAfterDocumentComplete);
   }

   LRESULT html_view::OnAfterDocumentComplete(WPARAM wparam, LPARAM lparam) 
   {
      string str;
      str = m_strTargetFrameName;
      if(gen::str::begins_eat(str, "WhiteboardSpecialFrameFor:MRTS"))
      {
         return 0;
      }

      if(m_estate == state_login)
      {
         m_estate = state_initial;
         Navigate(m_strAfterLogin);
      }
      return 0;
   }


   int html_view::OnCreate(LPCREATESTRUCT lpCreateStruct) 
   {
/*      if (::html_view::OnCreate(lpCreateStruct) == -1)
         return -1;*/
      
      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&System);

   //   papp->m_mousehook.SetCallbackWindow(GetTopLevelParent()->_get_handle());

      string str;
      LPMONIKER pmk;

      str.Format("%x", _get_handle());

      BSTR bstr = str.AllocSysString();

      CreateFileMoniker(bstr, &pmk);

      ModifyStyleEx(WS_BORDER, 0, SWP_FRAMECHANGED);   
      ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);   


      //OleStdRegisterAsRunning(this, pmk, &_dwROTcookie);

      
      
      return 0;
   }

   LRESULT html_view::OnExMouseMessage(WPARAM wparam, LPARAM lparam)
   {
   /*
               //System.simple_message_box("OnExMouseMessage", MB_OK);

      MSLLHOOKSTRUCT * pstruct = (MSLLHOOKSTRUCT *) lparam;

      HRESULT     hr;
      OLECHAR     szBuf[10];            // Place to put moniker
      LPMONIKER   pmk;

      COleVariant var;

      //IAccessible * acc.m_spAccessible;

      Accessible acc;
      Accessible acc2;
      
      acc.AttachFromPoint(&pstruct->pt);

      BSTR bstr = NULL;
      var.clear();
      var = (long) CHILDID_SELF;


      long lCount;
      hr = acc.GetChildCount(&lCount);

      IDispatch * pdispatch;
      IDispatch * pdispatch2;
      string strName;
      acc.m_spAccessible ->get_accName(var, &bstr);

      IAccessible * pacc2;
      COleVariant varAcc;
      string strValue;

      acc.m_spAccessible->accHitTest(pstruct->pt.x, pstruct->pt.y, &varAcc);

      if(varAcc.vt == VT_DISPATCH)
      {
         pdispatch = varAcc.pdispVal;
      }
      else if(varAcc.vt = VT_I4)
      {
         LONG l = varAcc.lVal;
      }




      acc.m_spAccessible->get_accName(var, &bstr);
      strName = bstr;
      acc.m_spAccessible->get_accValue(var, &bstr);
      strValue = bstr;

      COleVariant varId;
      COleVariant varRole;
      string strRole;

      varId = (long) CHILDID_SELF;

      hr = acc.m_spAccessible->get_accRole(varId, &varRole);
      hr = acc.m_spAccessible->get_accState(varId, &varRole);

      Accessible accParent;
      Accessible accChild;
      Accessible accItem;
      Accessible accNextItem;

      LONG lChildCount = 0;

      AccessibleArray acca;
      bool bParent = false;

      accItem.Attach(acc.m_spAccessible);
      while(true)
      {
         
         accItem.GetRoleText(strRole);
         accItem.GetName(strName);
         accItem.get_value(strValue);
         acca.add(accItem);

         if(bParent)
         {
            lChildCount = 0;
            accItem.GetChildCount(&lChildCount);
            bParent = false;
         }
         if(lChildCount > 0)
         {
            lChildCount--;
            if(accItem.GetChildByIndex(accNextItem, lChildCount) != S_OK)
               continue;
            if(acca.InArray(accNextItem))
               continue;
         }
         else
         {
            if(accItem.GetParent(accNextItem) != S_OK)
               break;
            bParent = true;
         }

         accItem.Attach(accNextItem);
      }

      string strParentName;
      string strParentValue;
      IAccessible * paccParent = NULL;
      IDispatch * pdispatchParent = NULL;
      acc.m_spAccessible->get_accParent(&pdispatchParent);
      if(pdispatchParent != NULL)
      {
         acc.m_spAccessible->get_accParent(&pdispatchParent);
         if(pdispatchParent != NULL)
         {
            pdispatchParent->QueryInterface(
               IID_IAccessible,
               (void **) &paccParent);
            if(paccParent != NULL)
            {
               paccParent->get_accName(var, &bstr);
               strParentName = bstr;
               paccParent->get_accValue(var, &bstr);
               strParentValue = bstr;
               LONG lObtained;
               COleVariant varChildren;
               AccessibleChildren(
                  acc.m_spAccessible,
                  0,
                  lCount,
                  &varChildren,
                  &lObtained);
               if(varChildren.vt == VT_DISPATCH)
               {
                  pdispatch = varChildren.pdispVal;
                  if(pdispatch != NULL)
                  {
                     pdispatch->QueryInterface(IID_IAccessible, (void **) &pacc2);
                     if(pacc2 != NULL)
                     {
                        long lCount = 0;
                        hr = pacc2->get_accChildCount(&lCount);

                        pacc2->get_accName(var, &bstr);
                        strName = bstr;
                        pacc2->get_accValue(var, &bstr);
                        strValue = bstr;
                        LONG lObtained;
                        COleVariant varChildren;
                        string strValue;
                        varChildren.clear();
                        hr = AccessibleChildren(
                           pacc2,
                           0,
                           lCount,
                           &varChildren,
                           &lObtained);
                        acc2.Attach(pacc2);

                        acc2.GetRoleText(strRole);
                        
                        if((varChildren.vt & VT_ARRAY) == VT_ARRAY) 
                        {
                           IAccessible * pacc2;
                           COleVariant varChild;
                           for(long l = 0; l < lObtained; l++)
                           {
                              pdispatch = NULL;
                              SafeArrayGetElement(varChildren.parray, &l, (void **) &varChild);
                              if(varChild.vt == VT_DISPATCH)
                              {

                                 pdispatch = varChild.pdispVal;
                                 if(pdispatch != NULL)
                                 {
                                    pdispatch->QueryInterface(IID_IAccessible, (void **) &pacc2);
                                    if(pacc2 != NULL)
                                    {
                                       acc.m_spAccessible->get_accName(var, &bstr);
                                       strName = bstr;
                                    }
                                    else
                                    {
                                       TYPEATTR  * pattr;
                                       ITypeInfo * ptypeinfo;
                                       pdispatch->GetTypeInfo(0, 0, &ptypeinfo);
                                       ptypeinfo->GetTypeAttr(&pattr);
         

                                    }
                                 }
                              }
                           }
                        }
                        else if(varChildren.vt == VT_DISPATCH)
                        {
                           pdispatch2 = varChildren.pdispVal;
                           if(pdispatch != NULL)
                           {
                              pdispatch2->QueryInterface(IID_IAccessible, (void **) &pacc2);
                              if(pacc2 != NULL)
                              {
                                 acc.m_spAccessible->get_accName(var, &bstr);
                                 strName = bstr;
                                 acc.m_spAccessible->get_accValue(var, &bstr);
                                 strValue = bstr;
                                 LONG lObtained;
                                 COleVariant varChildren;
                                 string strValue;
                                 AccessibleChildren(
                                    pacc2,
                                    0,
                                    lCount,
                                    &varChildren,
                                    &lObtained);

                              }
                           }
                        }
                        else if(varChildren.vt == VT_I4)
                        {
                           pdispatch2 = NULL;
                           pacc2->get_accChild(varChildren, &pdispatch2);
                           if(pdispatch2 != NULL)
                           {
                              pdispatch2->QueryInterface(IID_IAccessible, (void **) &pacc2);
                              if(pacc2 != NULL)
                              {
                                 acc.m_spAccessible->get_accName(var, &bstr);
                                 strName = bstr;
                                 acc.m_spAccessible->get_accValue(var, &bstr);
                                 strValue = bstr;
                              }
                           }
                           else
                           {
                              TYPEATTR  * pattr = NULL;
                              ITypeInfo * ptypeinfo = NULL;

                              long lTypeCount;
   /*                           pdispatch->GetTypeInfoCount(&lTypeCount);
                              for(long lType = 0; lType < lTypeCount; lType++)
                              {
                                 pdispatch->GetTypeInfo(lType, 0, &ptypeinfo);
                                 ptypeinfo->GetTypeAttr(&pattr);
                              }*/
                           /*}
                        }
                        else
                        {
                           IAccessible * pacc2;
                           COleVariant varChild;
                           for(long l = 0; l < lObtained; l++)
                           {
                              pdispatch = NULL;
                              SafeArrayGetElement(varChildren.parray, &l, (void **) &varChild);
                              if(varChild.vt == VT_DISPATCH)
                              {
                                 pdispatch = varChild.pdispVal;
                                 if(pdispatch != NULL)
                                 {
                                    pdispatch->QueryInterface(IID_IAccessible, (void **) &pacc2);
                                    if(pacc2 != NULL)
                                    {
                                       acc.m_spAccessible->get_accName(var, &bstr);
                                       strName = bstr;
                                    }
                                 }
                              }
                           }
                        }

                     }
                  }
               }
               else
               {
                  IAccessible * pacc2;
                  COleVariant varChild;
                  for(long l = 0; l < lObtained; l++)
                  {
                     pdispatch = NULL;
                     SafeArrayGetElement(varChildren.parray, &l, (void **) &varChild);
                     if(varChild.vt == VT_DISPATCH)
                     {
                        pdispatch = varChild.pdispVal;
                        if(pdispatch != NULL)
                        {
                           pdispatch->QueryInterface(IID_IAccessible, (void **) &pacc2);
                           if(pacc2 != NULL)
                           {
                              acc.m_spAccessible->get_accName(var, &bstr);
                              strName = bstr;
                           }
                        }
                     }
                  }
               }
            }
         }
      }


   //   string strRole;


      string strWindowText;
      string str;
      strWindowText = bstr;
      str.Format("http://cur1303x/elmdb/whiteboard/search.php?searchall=%s", strWindowText);

      /*HWND hwndParent = ::WindowFromPoint(pstruct->pt);
      if(hwndParent == NULL)
         return 0;
      POINT ptClient = pstruct->pt;
      ::ScreenToClient(hwndParent, &ptClient);
      HWND hwndChild = ::ChildWindowFromPointEx(hwndParent, ptClient, CWP_SKIPINVISIBLE);
      HWND hwnd;
      if(hwndChild != NULL)
         hwnd = hwndChild;
      else
         hwnd = hwndParent;

      string strBuf;

      strBuf.Format("%x", hwnd);

      BSTR bstr = strBuf.AllocSysString();

      CMonikerFile file;
      
      ITextDocument * pDoc = NULL;

      IBindCtx* pctx = NULL;

      CreateBindCtx(0, &pctx);
      CreateFileMoniker(bstr, &pmk);
      pmk->BindToObject(pctx, NULL, IID_ITextDocument, (void **) &pDoc);
      pctx->Release();

      string strWindowText;

      string str;

      ITextRange *   pRange;
      POINT          pt;
      IUnknown *     pUnk = NULL;
      
      ::ca::window * pwnd = ::ca::window::from_handle(hwnd);
      if(pDoc)
      {
         pDoc->RangeFromPoint(pt.x, pt.y, &pRange);
         BSTR bstr = NULL;
         pRange->GetText(&bstr);
         strWindowText = bstr;
         str.Format("http://cur1303x/elmdb/whiteboard/search.php?searchall=%s", strWindowText);
      }
      else
      {
         pwnd->GetWindowText(strWindowText);
         str.Format("http://cur1303x/elmdb/whiteboard/search.php?searchall=%s", strWindowText);
      }*/
      /*
      Navigate(str);

      GetParentFrame()->SetForegroundWindow();
      GetParentFrame()->ShowWindow(SW_RESTORE);
      GetParentFrame()->ShowWindow(SW_MINIMIZE);
      GetParentFrame()->ShowWindow(SW_RESTORE);
      GetParentFrame()->BringWindowToTop();

     */
      return 0;
   }


   void html_view::OnViewGoCalendar() 
   {
      document * pdoc = (document *) get_document();
      pdoc->update_all_views(NULL, document::HintShowCalendar, NULL);
   }

   void html_view::_001OnViewUserHour(gen::signal_object * pobj) 
   {
      document * pdoc = (document *) get_document();
      pdoc->update_all_views(NULL, document::HintShowUserHour, NULL);
   }

   void html_view::_001OnUpdateViewUserHour(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj);
      pcmdui->m_pcmdui->Enable();
   }

   void html_view::_001OnViewBookmark(gen::signal_object * pobj) 
   {
      document * pdoc = (document *) get_document();
      pdoc->update_all_views(NULL, document::HintShowBookmark, NULL);
   }

   void html_view::_001OnUpdateViewBookmark(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj);
      pcmdui->m_pcmdui->Enable();
   }


   void html_view::_001OnViewAnnotate(gen::signal_object * pobj) 
   {
      document * pdoc = (document *) get_document();
      pdoc->update_all_views(NULL, document::HintShowAnnotate, NULL);
   }

   void html_view::_001OnUpdateViewAnnotate(gen::signal_object * pobj) 
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj);
      pcmdui->m_pcmdui->Enable();
   }


   void html_view::Login(void)
   {
      m_estate = state_login;
      string strLogin;

      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&System);

      papp->GetSiteUrl(SiteLogin, strLogin);

      string strPost;
      string strUser;
      string strPassword;

      get_document()->GetUserOp(strUser);
      get_document()->GetUserPassword(strPassword);

      strPost.Format("::fontopus::user=%s&password=%s", strUser, strPassword);

      string strHeaders;

      strHeaders = "Content-Type: application/x-www-form-urlencoded\r\n";

   //   Navigate(strLogin, 0, 0, strHeaders, (LPVOID) (const char *) strPost, strPost.get_length() + 1);

   }

   void html_view::WBNavigate(const char * lpcszUrl)
   {
      string str;
      str = m_strTargetFrameName;
      if(gen::str::begins_eat(str, "WhiteboardSpecialFrameFor:MRTS"))
      {
         Navigate(lpcszUrl);
         return;
      }

      m_strAfterLogin = lpcszUrl;
      //Login();
      Navigate(lpcszUrl);
   }

   void html_view::OnBeforeNavigate2(html::data * pdata, const char * lpszUrl, DWORD nFlags, const char * lpszTargetFrameName, byte_array& baPostedData, const char * lpszHeaders, BOOL* pbCancel)
   {
      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&System);
      document * pdoc = (document *) get_document();
      string strUrl(lpszUrl);
      string strCmd(strUrl);

      if(!m_bSetTargetFrameName)
      {
         m_bSetTargetFrameName = true;
         if(lpszTargetFrameName != NULL)
         {
            m_strTargetFrameName = lpszTargetFrameName;
         }
         if(strUrl.make_lower().find("mrtsserv.") > 0
         && m_strTargetFrameName == "QUERYLIST")
         {
            pdoc->m_bMrtsQuerylist = true;
            pdoc->update_all_views(NULL, document::HintUpdateMrtsQuerylistTrayIcon);
         }
         
         if(!m_strTargetFrameName.is_empty())
         {
            pdoc->m_mapTargetHtmlView.set_at(m_strTargetFrameName, this);
         }
      }
      string str;
      string strReqTargetFrameName(lpszTargetFrameName);
      str = m_strTargetFrameName;
      if(gen::str::begins(str, "WhiteboardSpecialFrameFor:MRTSQueryList"))
      {
         get_document()->GetRootView()->set_cur_tab_by_id(
            whiteboard::view::ViewMrtsQuerylistHtml);
      }
      else if(gen::str::begins(str, "WhiteboardSpecialFrameFor:MRTS"))
      {
         get_document()->GetRootView()->set_cur_tab_by_id(
            whiteboard::view::ViewMrtsHtml);
      }

      /*
      string str;
      str = m_strTargetFrameName;
      if(gen::str::begins_eat(str, "WhiteboardSpecialFrameFor:MRTS"))
      {
         html_view::OnBeforeNavigate2(lpszUrl, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
         return;
      }
      */


      string strLoUrl = strUrl;
      strLoUrl.make_lower();
      whiteboard::main_frame * pframe = dynamic_cast < whiteboard::main_frame * > (GetTopLevelFrame());
      if(base < whiteboard::main_frame >::bases(pframe))
      {
         if(strLoUrl.find("mrtsserv.") >= 0)
         {
            pframe->SetMrtsStyle();
      //      System.simple_message_box("MRTS URL");
         }
         else
         {
            pframe->SetNormalStyle();
         }
      }

      string strUserHourUrl;

   //   whiteboard::application * papp = (whiteboard::application *) &System;

   //   GetUserHourDir(strUserHourUrl);


      if(gen::str::begins_eat_ci(strCmd, strUserHourUrl))
      {
         string strPath;
         //userhour_create_file(lpszUrl, strCmd);
         //Navigate(strPath);
      }
      else if(gen::str::begins_eat(strCmd, "wb://"))
      {
         string strPath;
         //wb_create_file(strPath, strCmd);
         Navigate(strPath);
         *pbCancel = TRUE;
      }
   /*   else
      {
         *pbCancel = FALSE;
         html_view::OnBeforeNavigate2(lpszURL, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
      }*/

   //   html_view::OnBeforeNavigate2(lpszUrl, nFlags, lpszTargetFrameName, baPostedData, lpszHeaders, pbCancel);
   }




   void html_view::OnSize(UINT nType, int cx, int cy)
   {
   //   __super::OnSize(nType, cx, cy);

      // TODO: add your message handler code here
   }

   bool html_view::_001OnCmdMsg(BaseCmdMsg * pcmdmsg) 
   {
      if(__super::_001OnCmdMsg(pcmdmsg))
         return TRUE;
      if(!base < userbase::frame_window >::bases(GetParent()))
      {
         if(GetParent()->_001OnCmdMsg(pcmdmsg))
          return TRUE;
      }
      return FALSE;
   }



   void html_view::OnNewWindow2(LPDISPATCH* ppDisp, BOOL* Cancel)
   {
   /*   if(m_strTargetFrameName == "WhiteboardSpecialFrameFor:MRTS")
      {
         html_view * pview = get_document()->GetRootView()->m_phtmlviewMrtsQuerylist =
            dynamic_cast < html_view *> (get_document()->GetRootView()->CreateView(view::ViewMrtsQuerylistHtml));
         if(pview != NULL)
         {
            pview->m_bSetTargetFrameName = true;
            get_document()->m_bMrtsQuerylist = true;
            get_document()->update_all_views(NULL, document::HintUpdateMrtsQuerylistTrayIcon);
            pview->m_strTargetFrameName = "WhiteboardSpecialFrameFor:MRTSQueryList";
         }
   //      *ppDisp = pview->GetApplication();
      }
      else*/
      {
         whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&System);
         html_view * pview = papp->m_ptemplate->CreateHtmlWnd(true);
   //      *ppDisp = pview->GetApplication();
      }
   }

} // namespace whiteboard