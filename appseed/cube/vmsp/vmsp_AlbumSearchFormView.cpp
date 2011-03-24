#include "StdAfx.h"
#include "AlbumSearchFormView.h"

#include "AlbumSongList.h"

AlbumSearchFormView::AlbumSearchFormView(::ca::application * papp) :
   ca(papp),
   ::userbase::view(papp),
   m_brushBackground(papp, GetSysColor(COLOR_WINDOW)),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::userbase::scroll_view(papp),
   ::userbase::form_view(papp),
   html_form(papp),
   html_form_view(papp),
   form_view(papp),
   ::user::form(papp),
   m_buttonSelectAll(papp),
   m_buttonSelectNone(papp),
   m_buttonSearch(papp)
{
   //{{AFX_DATA_INIT(AlbumSearchFormView)
      // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
    m_crBackground = GetSysColor(COLOR_WINDOW);
    m_crForeground = GetSysColor(COLOR_WINDOWTEXT);
   m_plist = NULL;

}

AlbumSearchFormView::~AlbumSearchFormView()
{
}

/*void AlbumSearchFormView::DoDataExchange(CDataExchange* pDX)
{
   //form_view::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AlbumSearchFormView)
   //DDX_Control(pDX, IDC_BUTTON_SELECTALL, m_buttonSelectAll);
   //DDX_Control(pDX, IDC_BUTTON_SELECTNONE, m_buttonSelectNone);
   //DDX_Control(pDX, IDC_BUTTON_SEARCH, m_buttonSearch);
/*   DDX_Control(pDX, IDC_COMBO_SEARCH, m_comboSearch);
   DDX_Control(pDX, IDC_LIST_CHECK, m_listCheck);*/
   //}}AFX_DATA_MAP
//}


 // BEGIN_MESSAGE_MAP(AlbumSearchFormView, form_view)
   //{{AFX_MSG_MAP(AlbumSearchFormView)
/*   ON_WM_CTLCOLOR()
   ON_BN_CLICKED(IDC_BUTTON_SEARCH, OnButtonSearch)
   ON_BN_CLICKED(IDC_BUTTON_SELECTALL, OnButtonSelectall)
   ON_BN_CLICKED(IDC_BUTTON_SELECTNONE, OnButtonSelectnone)
   ON_EN_CHANGE(IDC_EDIT, OnChangeEdit)
   ON_CBN_EDITCHANGE(IDC_COMBO_SEARCH, OnEditchangeComboSearch)
   ON_CBN_SELENDOK(IDC_COMBO_SEARCH, OnSelendokComboSearch)
   ON_WM_CREATE()
   //}}AFX_MSG_MAP*/
 // END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlbumSearchFormView diagnostics


#ifdef _DEBUG
void AlbumSearchFormView::assert_valid() const
{
   form_view::assert_valid();
}

void AlbumSearchFormView::dump(dump_context & dumpcontext) const
{
   form_view::dump(dumpcontext);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// AlbumSearchFormView message handlers

HBRUSH AlbumSearchFormView::OnCtlColor(::ca::graphics * pgraphics, ::ca::window* pWnd, UINT nCtlColor) 
{
   throw not_implemented_exception();
   //HBRUSH hbr = form_view::OnCtlColor(pgraphics, pWnd, nCtlColor);
      /*HBRUSH hbr;
   if(nCtlColor == CTLCOLOR_EDIT)
   {
      pgraphics->SetTextColor(m_crForeground);
      hbr = m_brushBackground;
      pgraphics->SetBkColor(m_crBackground);
   }
   else if(nCtlColor == CTLCOLOR_MSGBOX)
   {
      hbr = m_brushBackground;
   }
   else if(nCtlColor == CTLCOLOR_STATIC)
   {
      pgraphics->SetTextColor(m_crForeground);
      hbr = m_brushBackground;
      pgraphics->SetBkColor(m_crBackground);
   }
   else if(nCtlColor == CTLCOLOR_DLG)
   {
//      pgraphics->SetTextColor(RGB(255, 255, 255));
      hbr = m_brushBackground;
//      pgraphics->SetBkColor(RGB(0, 0, 0));
   }
   else
   {
//      hbr = form_view::OnCtlColor(pgraphics, pWnd, nCtlColor);
   }
   // TODO: Change any attributes of the DC here
   
   // TODO: Return a different brush if the default is not desired
   return hbr;*/
}

int AlbumSearchFormView::GetSearchMask()
{
int iMask = 0;

/*    if(m_listCheck.get_check(0) == 1)
        iMask |= CDBSongRowBase::maskName;

    if(m_listCheck.get_check(1) == 1)
        iMask |= CDBSongRowBase::maskAuthor;

    if(m_listCheck.get_check(2) == 1)
        iMask |= CDBSongRowBase::maskCopyright;

    if(m_listCheck.get_check(3) == 1)
        iMask |= CDBSongRowBase::maskComposer;

    if(m_listCheck.get_check(4) == 1)
        iMask |= CDBSongRowBase::maskLyricist;

    if(m_listCheck.get_check(5) == 1)
        iMask |= CDBSongRowBase::maskArranger;

    if(m_listCheck.get_check(6) == 1)
        iMask |= CDBSongRowBase::maskPerformer;

    if(m_listCheck.get_check(7) == 1)
        iMask |= CDBSongRowBase::maskProgrammer;
    
    if(m_listCheck.get_check(8) == 1)
        iMask |= CDBSongRowBase::maskKeyword;

    if(m_listCheck.get_check(9) == 1)
        iMask |= CDBSongRowBase::maskPath;*/

    return iMask;

}

void AlbumSearchFormView::OnInitialUpdate() 
{
//   form_view::OnInitialUpdate();
   string str;
    
/*    str.load_string(IDS_ALBUM_SONGNAME);
   m_listCheck.AddString(str);

    str.load_string(IDS_ALBUM_AUTHOR);
   m_listCheck.AddString(str);
    
   str.load_string(IDS_ALBUM_COPYRIGHT);
   m_listCheck.AddString(str);

    str.load_string(IDS_ALBUM_COMPOSER);
   m_listCheck.AddString(str);

    str.load_string(IDS_ALBUM_LYRICIST);
   m_listCheck.AddString(str);

    str.load_string(IDS_ALBUM_ARRANGER);
   m_listCheck.AddString(str);

    str.load_string(IDS_ALBUM_PERFORMER);
   m_listCheck.AddString(str);

    str.load_string(IDS_ALBUM_PROGRAMMER);
   m_listCheck.AddString(str);

    str.load_string(IDS_ALBUM_KEYWORD);
   m_listCheck.AddString(str);

    str.load_string(IDS_ALBUM_PATH);
   m_listCheck.AddString(str);*/

    OnButtonSelectall();

    UpdateSearchEnable();

//    CVMSApp * pApp = (CVMSApp *) &System;
/*    CDBCentral * pDataCentral = (CDBCentral *) db();
    CDataSource * pDataSource = pDataCentral->GetDataSource();
   HRESULT hr;
    try
    {
      if(FAILED(hr = m_tableSearch.OpenIndexed(
         pDataSource,
         OLESTR("AlbumSearch"),
         OLESTR("PrimaryKey"),
         CDBTableV004::Indexed)))
      {
         hr = m_tableSearch.open(pDataSource, "AlbumSearch");
      }
    } catch(COLEDBException *e)
   {
      CDBErrorDialog dlg;
      dlg.Init(e->m_spUnk, e->m_iid);
      dlg.DoModal();
      e->Delete();
   }*/
    string strSearch = GetSearchText();
    FillSearchCombo(strSearch);
   // TODO: add your specialized code here and/or call the base class
   
}

void AlbumSearchFormView::OnButtonSearch() 
{
   // TODO: add your control notification handler code here
    SearchNow();
}

void AlbumSearchFormView::OnButtonSelectall() 
{
   // TODO: add your control notification handler code here
/*   int iCount = m_listCheck.get_count();
    for(int i = 0; i < iCount; i++)
    {
        m_listCheck.SetCheck(i, 1);
    }*/
}

void AlbumSearchFormView::OnButtonSelectnone() 
{
   // TODO: add your control notification handler code here
/*   int iCount = m_listCheck.get_count();
    for(int i = 0; i < iCount; i++)
    {
        m_listCheck.SetCheck(i, 0);
    }*/
}

string AlbumSearchFormView::GetSearchText()
{
    //user::edit_plain_text * pEdit = (user::edit_plain_text *) GetDlgItem(IDC_EDIT);
    string str;
    //pEdit->GetWindowText(str);
/*    m_comboSearch.GetWindowText(str);
    if(str.is_empty())
    {
        int iSel = m_comboSearch.get_cur_sel();
        if(iSel != CB_ERR)
        {
            m_comboSearch.GetLBText(iSel, str);
        }
    }*/
    return str;

}

BOOL AlbumSearchFormView::PreCreateWindow(CREATESTRUCT& cs) 
{
   // TODO: add your specialized code here and/or call the base class
   
    cs.dwExStyle |= WS_EX_CLIENTEDGE;

   return form_view::PreCreateWindow(cs);
}

void AlbumSearchFormView::OnChangeEdit() 
{
   // TODO: If this is a RICHEDIT control, the control will not
   // send this notification unless you override the form_view::OnInitDialog()
   // function and call CRichEditCtrl().SetEventMask()
   // with the ENM_CHANGE flag ORed into the mask.
    UpdateSearchEnable();
   // TODO: add your control notification handler code here
   
}

void AlbumSearchFormView::UpdateSearchEnable()
{
   string str = GetSearchText();
//    user::edit_plain_text * pEdit = (user::edit_plain_text *) GetDlgItem(IDC_EDIT);
   simple_button * pButton = dynamic_cast < simple_button * > (GetDlgItem("IDC_BUTTON_SEARCH"));
  //  pEdit->GetWindowText(str);
/*    if(str.is_empty())
    {
        pButton->EnableWindow(FALSE);
    }
    else
    {
        pButton->EnableWindow();
    }*/
}

void AlbumSearchFormView::OnEditchangeComboSearch() 
{
   // TODO: add your control notification handler code here
/*    DWORD dwSel = m_comboSearch.GetEditSel();
    int iStartSel = LOWORD(dwSel);
    int iEndSel = HIWORD(dwSel);
    string strSearch;
    strSearch = GetSearchText();
    if(iStartSel == 0xff)
        iStartSel = -1;
    if(iEndSel == 0xff)
        iEndSel = -1;

   FillSearchCombo(strSearch);
    if(m_comboSearch.get_count())
    {
        m_comboSearch.ShowDropDown();
    }
    else
    {
        m_comboSearch.ShowDropDown(false);
    }

    
    m_comboSearch.SetWindowText(strSearch);
    m_comboSearch.SetEditSel(iStartSel , iEndSel);*/
    UpdateSearchEnable();
}

void AlbumSearchFormView::FillSearchCombo(string strSearchText)
{
/*    m_comboSearch.ResetContent();
   if(db()->IsWorking())
   {
      stringa strArray;
      m_tableSearch.AddTextsStartingWith(strSearchText, strArray);
      for(int i = 0; i < strArray.get_size(); i++)
      {
         m_comboSearch.AddString(strArray[i]);
      }
   }*/
}


void AlbumSearchFormView::OnSelendokComboSearch() 
{
   // TODO: add your control notification handler code here
   UpdateSearchEnable();
}

VMSRESULT AlbumSearchFormView::SearchNow()
{
/*   ::ca::window * pWnd = GetParent();

    string strSearch = GetSearchText();

    CBSTR::copy(m_tableSearch.m_bstrText, strSearch);

    m_tableSearch.Insert(0);

   m_plist->SetWhereClause(
      GetSearchMask(),
      GetSearchText());
    m_plist->UpdateList(NULL);
   int iCount = m_plist->m_dwaQueryKeys.get_size();


    pWnd->PostMessage(WM_USER, 2, iCount);*/
    return VMSR_SUCCESS;
}

int AlbumSearchFormView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
/*   if (form_view::OnCreate(lpCreateStruct) == -1)
      return -1;*/
   
   // TODO: add your specialized creation code here
   
   return 0;
}

bool AlbumSearchFormView::SetAlbumSongList(AlbumSongList *plist)
{
   m_plist = plist;
   return true;
}

/*
BOOL AlbumSearchFormView::create(
   const char * lpcszClassName,
   const char * lpcszWindowName,
   DWORD dwStyle,
   const RECT &rect,
   ::ca::window * pwndParent,
   UINT uiID,
   create_context * pcontext)
{

/*   return form_view::create(
      lpcszClassName,
      lpcszWindowName,
      dwStyle,
      rect,
      pwndParent,
      uiID,
      pcontext);

*/
   /*return TRUE;
}*/

void AlbumSearchFormView::_001InitializeFormPreData()
{
   class user::control::descriptor control;

   control.m_bTransparent = true;
   control.set_type(user::control::type_static);
   control.m_id = "IDC_ST_SEARCH_ICON";
   control.add_function(user::control::function_static);
   _001AddControl(control);

   control.m_bTransparent = true;
   control.set_type(user::control::type_static);
   control.m_id = "IDC_ST_SEARCH_TITLE";
   control.add_function(user::control::function_static);
   _001AddControl(control);

   control.m_bTransparent = true;
   control.set_type(user::control::type_static);
   control.m_id = "IDC_ST_SEARCH_COMBO";
   control.add_function(user::control::function_static);
   _001AddControl(control);
   
   control.m_bTransparent = true;
   control.set_type(user::control::type_static);
   control.m_id = "IDC_ST_SEARCH_OPTIONS";
   control.add_function(user::control::function_static);
   _001AddControl(control);

}

