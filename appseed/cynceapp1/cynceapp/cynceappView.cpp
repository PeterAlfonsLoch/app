// cynceappView.cpp : implementation of the CcynceappView class
//

#include "stdafx.h"
#include "cynceapp.h"

#include "cynceappDoc.h"
#include "cynceappView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcynceappView

IMPLEMENT_DYNCREATE(CcynceappView, CFormView)

BEGIN_MESSAGE_MAP(CcynceappView, CFormView)
   ON_WM_TIMER()
   ON_WM_CREATE()
END_MESSAGE_MAP()

// CcynceappView construction/destruction

CcynceappView::CcynceappView()
	: CFormView(CcynceappView::IDD)
{
	// TODO: add construction code here

}

CcynceappView::~CcynceappView()
{
}

void CcynceappView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CcynceappView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CcynceappView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}


// CcynceappView diagnostics

#ifdef _DEBUG
void CcynceappView::AssertValid() const
{
	CFormView::AssertValid();
}

void CcynceappView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CcynceappDoc* CcynceappView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CcynceappDoc)));
	return (CcynceappDoc*)m_pDocument;
}
#endif //_DEBUG


// CcynceappView message handlers

void CcynceappView::OnTimer(UINT_PTR nIDEvent)
{
   if(nIDEvent == 1)
   {
      UpdateHostIp();
   }
   CFormView::OnTimer(nIDEvent);
}

void CcynceappView::GetHostIp(CString & strIp)
{
   WORD wVersionRequested;
   WSADATA wsaData;
   char name[255];
   PHOSTENT hostinfo;
   wVersionRequested = MAKEWORD( 1, 1 );
   char *ip;
   CString str;

   if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
   {
      if( gethostname ( name, sizeof(name)) == 0)
      {
         str.Format("Host name: %s\n", name);
         strIp += str;

         if((hostinfo = gethostbyname(name)) != NULL)
         {
            int nCount = 0;
            while(hostinfo->h_addr_list[nCount])
            {
               ip = inet_ntoa(*(struct in_addr *)hostinfo->h_addr_list[nCount]);
               str.Format("IP #%d: %s\n", ++nCount, ip);
               strIp += str;
            }
         }
      }
   }
}

void CcynceappView::UpdateHostIp(void)
{
   CString strIp;
   GetHostIp(strIp);
   GetDlgItem(IDC_EDIT_HOSTIP)->SetWindowText(strIp);
}

int CcynceappView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   if (CFormView::OnCreate(lpCreateStruct) == -1)
      return -1;


   UpdateHostIp();
   SetTimer(1, 30 * 1000, NULL);

   return 0;
}
