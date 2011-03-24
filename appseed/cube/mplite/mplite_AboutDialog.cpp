#include "StdAfx.h"

/////////////////////////////////////////////////////////////////////////////
// AboutDlg dialog used for App About
/*
class AboutDlg : public ::userbase::form
{
public:
   AboutDlg(::ca::application * papp);

   ::ca::brush m_brushStatic;
   COLORREF m_crStaticBackground;
   ::ca::bitmap m_bitmapBackground;
   ::ca::graphics_sp m_dcBackground;

   void _001InitializeFormPreData();
   void _001OnDraw(::ca::graphics * pdc);

// Dialog Data
   //{{AFX_DATA(AboutDlg)
   enum { IDD = IDD_ABOUTBOX };
//   CStatic   m_stTitle;
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AboutDlg)
   //}}AFX_VIRTUAL

   DECL_GEN_SIGNAL(_001OnEnable)

   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

// Implementation
protected:
   //{{AFX_MSG(AboutDlg)
   //afx_msg void OnPaint();
   virtual BOOL OnInitDialog();
   afx_msg HBRUSH OnCtlColor(::ca::graphics * pgraphics, ::ca::window* pWnd, UINT nCtlColor);
   //}}AFX_MSG
//   ()
};

AboutDlg::AboutDlg(::ca::application * papp) :
   ::userbase::form(papp, AboutDlg::IDD),
   ::user::interaction(papp)
{
   m_crStaticBackground = RGB(64, 128, 255);
   //m_brushStatic.CreateSolidBrush(m_crStaticBackground);
   m_brushStatic.CreateStockObject(NULL_BRUSH);
   //{{AFX_DATA_INIT(AboutDlg)
   //}}AFX_DATA_INIT
}

/*
 // BEGIN_MESSAGE_MAP(AboutDlg, ::userbase::form)
   //{{AFX_MSG_MAP(AboutDlg)
// xxx   ON_WM_CTLCOLOR()
   //}}AFX_MSG_MAP
 // END_MESSAGE_MAP()
*/

  /* void AboutDlg::_001OnDraw(::ca::graphics * pdc) 
{
   ::ca::graphics_sp & spgraphics = *pdc;

   rect rectClient;

   _001GetClientRect(rectClient);

   if(m_dcBackground.get_os_data() == NULL)
   {
      m_dcBackground.CreateCompatibleDC(&spgraphics);
      HBITMAP hbitmap = System.imaging().LoadBitmap(
         "PNG",
         MAKEINTRESOURCE(IDR_PNG_VMPLITE_ABOUT));
      m_bitmapBackground.Attach(hbitmap);
      m_dcBackground.SelectObject(m_bitmapBackground);
   }

/*   TRIVERTEX        vert[2] ;
   GRADIENT_RECT    gRect;
   vert [0] .x      = rectClient.left;
   vert [0] .y      = rectClient.top;
   vert [0] .Red    = 0x0000;
   vert [0] .Green  = 0x0000;
   vert [0] .Blue   = 0x0000;
   vert [0] .Alpha  = 0x0000;

   vert [1] .x      = rectClient.right;
   vert [1] .y      = rectClient.bottom; 
   vert [1] .Red    = 0x0000;
   vert [1] .Green  = 0x0000;
   vert [1] .Blue   = 0xff00;
   vert [1] .Alpha  = 0x0000;

   gRect.UpperLeft  = 0;
   gRect.LowerRight = 1;
   GradientFill(spgraphics,vert,2,&gRect,1,GRADIENT_FILL_RECT_H);*/

   //spgraphics->FillSolidRect(rectClient, m_crStaticBackground);
   /*spgraphics->BitBlt(
      rectClient.left,
      rectClient.top,
      rectClient.width(),
      rectClient.height(),
      &m_dcBackground,
      0,
      0,
      SRCCOPY);


   spgraphics->Draw3dRect(rectClient, RGB(92, 127, 192), RGB(92, 127, 192));

   rect rect(rectClient);
   rect.deflate(1, 1, 1, 1);
   spgraphics->Draw3dRect(rectClient, RGB(64, 92, 127), RGB(64, 92, 127));
   
}

void AboutDlg::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
{
   ::userbase::form::_001InstallMessageHandling(pinterface);
   IGUI_WIN_MSG_LINK(WM_ENABLE, pinterface, this, &AboutDlg::_001OnEnable);

}

void AboutDlg::_001OnEnable(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::enable, penable, pobj);
   BOOL bEnable = penable->get_enable();
}


BOOL AboutDlg::OnInitDialog() 
{
   ::userbase::form::OnInitDialog();

   string str;

   str.Format("veriwell Musical Player Lite");


   application * papp = dynamic_cast < application * > (&System);

   char lpszModuleFilePath[MAX_PATH + 1];
   GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

   DWORD dw;
   
   DWORD dwResSize = GetFileVersionInfoSize(      
      lpszModuleFilePath,
      &dw);


   if(dwResSize > 0)
   {
      LPVOID lpdata = new BYTE[dwResSize];
      if(GetFileVersionInfo(      
         lpszModuleFilePath,
         0,
         dwResSize,
         lpdata))
      {
         UINT cbTranslate;
         struct LANGANDCODEPAGE {
            WORD wLanguage;
            WORD wCodePage;
            } *lpTranslate;

         // read the list of languages and code pages.

         VerQueryValue(lpdata, 
              TEXT("\\VarFileInfo\\Translation"),
              (LPVOID*)&lpTranslate,
              &cbTranslate);

         string strKey;
         //for( i=0; i < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); i++ )
         for(int i=0; i < 1; i++ )
         {
           LPTSTR lpsz;
           UINT uiSize;

           strKey.Format(
            TEXT("\\StringFileInfo\\%04x%04x\\FileDescription"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);

           string strValue;

           

           // Retrieve file description for language and code page "i". 
           VerQueryValue(lpdata, 
                         (LPTSTR) (const char *) strKey, 
                         (LPVOID *)&lpsz, 
                         &uiSize); 

           strValue = lpsz;

           if(uiSize > 0)
           {
               str = strValue;
           }

           strKey.Format(
            TEXT("\\StringFileInfo\\%04x%04x\\FileVersion"),
            lpTranslate[i].wLanguage,
            lpTranslate[i].wCodePage);

           // Retrieve file description for language and code page "i". 
           VerQueryValue(lpdata, 
                         (LPTSTR) (const char *) strKey, 
                         (LPVOID *)&lpsz, 
                         &uiSize); 


           string strVersion(lpsz, uiSize);

           str += " " + strVersion;
         }
      }
      delete [] (LPBYTE) lpdata;
   }


   
   GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(str);
   
   return TRUE;  // return TRUE unless you set the focus to a control
                 // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH AboutDlg::OnCtlColor(::ca::graphics * pdc, ::ca::window* pWnd, UINT nCtlColor) 
{
   HBRUSH hbr = ::userbase::form::OnCtlColor(pdc, pWnd, nCtlColor);
   
   if(nCtlColor == CTLCOLOR_STATIC)
   {
      pdc->SetBkMode(TRANSPARENT);
      //pdc->SetBkColor(m_crStaticBackground);
      return m_brushStatic;
   }
   return hbr;
}

void AboutDlg::_001InitializeFormPreData()
{
   user::control::descriptor control;

   control.m_uiId = IDOK;
   control.m_typeinfo = &typeid(simple_button);
   _001AddControl(control);

   control.m_uiId = IDC_STATIC_ICON;
   control.m_typeinfo = &typeid(simple_button);
   _001AddControl(control);

   control.m_uiId = IDC_STATIC_TITLE;
   control.m_typeinfo = &typeid(simple_button);
   _001AddControl(control);

   control.m_uiId = IDC_STATIC_COPYRIGHT;
   control.m_typeinfo = &typeid(simple_button);
   _001AddControl(control);
}


// App command to run the dialog
void application::OnAppAbout()
{
   AboutDlg aboutDlg(this);
   aboutDlg.DoModal();
}

*/

