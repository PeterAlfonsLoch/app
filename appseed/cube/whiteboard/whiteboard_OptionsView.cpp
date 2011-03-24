#include "StdAfx.h"

namespace whiteboard
{

   options_view::options_view(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp),   
      ::userbase::view(papp),
      ::user::scroll_view(papp),
      ::userbase::scroll_view(papp),
      ::userbase::form_view(papp),
      ::user::form(papp),
      html_form(papp),
      html_form_view(papp),
      form_view(papp)
   {
   }

   options_view::~options_view()
   {
   }

/*   void options_view::DoDataExchange(CDataExchange* pDX)
   {
   /* linux   form_view::DoDataExchange(pDX);

      DDX_Control(pDX, IDC_COMBO_SITE_TAG, m_comboSiteTag);
      DDX_Control(pDX, IDC_EDIT_SITE_URL, m_editSiteUrl);

      if(!pDX->m_bSaveAndValidate)
      {
         {
            simple_button * pbutton = (simple_button *) GetDlgItem(IDC_CHECK_SHOW_TRAY_ICON_MRTS);
            pbutton->SetCheck(get_document()->GetShowMrtsTrayIcon());
         }
         {
            simple_button * pbutton = (simple_button *) GetDlgItem(IDC_CHECK_SHOW_TRAY_ICON_MRTS_QUERYLIST);
            pbutton->SetCheck(get_document()->GetShowableMrtsQuerylistTrayIcon());
         }
         {
            simple_button * pbutton = (simple_button *) GetDlgItem(IDC_CHECK_SHOW_CALENDAR_TRAY_ICON);
            pbutton->SetCheck(get_document()->GetShowCalendarTrayIcon());
         }
      } */
   //}

    // BEGIN_MESSAGE_MAP(options_view, form_view)
   /*   ON_EN_CHANGE(IDC_EDIT_NICK, OnEnChangeEditNick)
      ON_EN_CHANGE(IDC_EDIT_PASSWORD, OnEnChangeEditPassword)
      ON_CBN_SELCHANGE(IDC_COMBO_SITE_TAG, OnCbnSelchangeComboSiteTag)
      ON_EN_CHANGE(IDC_EDIT_SITE_URL, OnEnChangeEditSiteUrl)
      ON_BN_CLICKED(IDC_CHECK_SHOW_TRAY_ICON_MRTS, OnBnClickedCheckShowTrayIconMrts)
      ON_BN_CLICKED(IDC_CHECK_SHOW_CALENDAR_TRAY_ICON, OnBnClickedCheckShowCalendarTrayIcon)
      ON_BN_CLICKED(IDC_CHECK_SHOW_TRAY_ICON_MRTS_QUERYLIST, OnBnClickedCheckShowTrayIconMrtsQuerylist)*/
    // END_MESSAGE_MAP()


   // options_view diagnostics

   #ifdef _DEBUG
   void options_view::assert_valid() const
   {
      form_view::assert_valid();
   }

   void options_view::dump(dump_context & dumpcontext) const
   {
      form_view::dump(dumpcontext);
   }

   document* options_view::get_document()
      { return dynamic_cast <  document  * > (::view::get_document()); }

   #endif //_DEBUG


   // options_view message handlers

   bool options_view::_001OnCmdMsg(BaseCmdMsg * pcmdmsg) 
   {
      if(__super::_001OnCmdMsg(pcmdmsg))
         return TRUE;
      if(GetParent()->_001OnCmdMsg(pcmdmsg))
         return TRUE;
      return FALSE;
   }

   void options_view::OnEnChangeEditNick()
   {
      /* linux
      user::edit_plain_text * pedit = (user::edit_plain_text *) GetDlgItem(IDC_EDIT_NICK);

      string str;
      pedit->GetWindowText(str);

      System.WriteProfileString("Options", "Nick", str);
   */
   }

   void options_view::OnEnChangeEditPassword()
   {
   /* linux   user::edit_plain_text * pedit = (user::edit_plain_text *) GetDlgItem(IDC_EDIT_PASSWORD);

      string str;
      pedit->GetWindowText(str);

      get_document()->SetUserPassword(str);
   */
   }

   void options_view::OnInitialUpdate()
   {
   /*  linux form_view::_001OnInitialUpdate(NULL);

      string str;

      user::edit_plain_text * pedit = (user::edit_plain_text *) GetDlgItem(IDC_EDIT_NICK);
      str = System.GetProfileString("Options", "Nick", "");
      pedit->SetWindowText(str);

      pedit = (user::edit_plain_text *) GetDlgItem(IDC_EDIT_PASSWORD);
      get_document()->GetUserPassword(str);
      pedit->SetWindowText(str);

      m_comboSiteTag.ResetContent();

      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&System);

      int iSiteCount = papp->GetSiteCount();
      for(int iSite = 0; iSite < iSiteCount; iSite++)
      {
         site * psite = papp->GetSite(iSite);
         m_comboSiteTag.InsertString(iSite, psite->m_strTag);
      }
     */ 
   }

   void options_view::OnCbnSelchangeComboSiteTag()
   {
   /* linux   int iSel = m_comboSiteTag.get_cur_sel();
      if(iSel == CB_ERR)
         return;
      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&System);
      string strUrl;
      site * psite = papp->GetSite(iSel);
      papp->GetSiteUrl(psite->m_esite, strUrl);
      m_editSiteUrl.SetWindowText(strUrl); */
   }

   void options_view::OnEnChangeEditSiteUrl()
   {
   /* linux   int iSel = m_comboSiteTag.get_cur_sel();
      if(iSel == CB_ERR)
         return;
      whiteboard::application * papp = dynamic_cast < whiteboard::application * > (&System);
      string strUrl;
      m_editSiteUrl.GetWindowText(strUrl);
      site * psite = papp->GetSite(iSel);
      papp->SetSiteUrl(psite->m_esite, strUrl); */
   }

   void options_view::OnBnClickedCheckShowTrayIconMrts()
   {
   /* linux   simple_button * pbutton = (simple_button *) GetDlgItem(IDC_CHECK_SHOW_TRAY_ICON_MRTS);
      bool bShow = pbutton->get_check() == 1;
      document * pdoc = get_document();
      pdoc->ShowMrtsTrayIcon(bShow); */
   }

   void options_view::OnBnClickedCheckShowTrayIconMrtsQuerylist()
   {
   /* linux   simple_button * pbutton = (simple_button *) GetDlgItem(IDC_CHECK_SHOW_TRAY_ICON_MRTS_QUERYLIST);
      bool bShow = pbutton->get_check() == 1;
      document * pdoc = get_document();
      pdoc->SetShowableMrtsQuerylistTrayIcon(bShow); */
   }

   void options_view::OnBnClickedCheckShowCalendarTrayIcon()
   {
   /* linux   simple_button * pbutton = (simple_button *) GetDlgItem(IDC_CHECK_SHOW_CALENDAR_TRAY_ICON);
      bool bShow = pbutton->get_check() == 1;
      document * pdoc = get_document();
      pdoc->ShowCalendarTrayIcon(bShow);*/
   }

} // namespace whiteboard