// vmsnettomidiView.cpp : implementation of the CVmsnettomidiView class
//

#include "stdafx.h"
#include "vmsnettomidi.h"

#include "vmsnettomidiDoc.h"
#include "vmsnettomidiView.h"

#include "NetToMidiServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void SetAddress(CIPAddressCtrl & ctrl, LPCTSTR lpcsz)
{
   UINT b1, b2, b3, b4;
   sscanf( lpcsz, "%u.%u.%u.%u", &b1, &b2, &b3, &b4 );
   ctrl.SetAddress(b1, b2, b3, b4);
}
void GetAddress(CIPAddressCtrl & ctrl, CString & str)
{
   UINT b1, b2, b3, b4;
   ctrl.GetAddress((BYTE & )b1, (BYTE & )b2, (BYTE & )b3, (BYTE & )b4);
   str.Format( "%u.%u.%u.%u", b1, b2, b3, b4 );
}

/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiView

IMPLEMENT_DYNCREATE(CVmsnettomidiView, CFormView)

BEGIN_MESSAGE_MAP(CVmsnettomidiView, CFormView)
	//{{AFX_MSG_MAP(CVmsnettomidiView)
	ON_UPDATE_COMMAND_UI(ID_ACTION_STOP, OnUpdateActionStop)
	ON_COMMAND(ID_ACTION_STOP, OnActionStop)
	ON_EN_CHANGE(IDC_EDIT_REMOTE_SERVER_PORT, OnChangeEditRemoteServerPort)
	ON_EN_CHANGE(IDC_EDIT_LOCAL_SERVER_PORT, OnChangeEditLocalServerPort)
	ON_COMMAND(ID_ACTION_CALL, OnActionCall)
	ON_UPDATE_COMMAND_UI(ID_ACTION_CALL, OnUpdateActionCall)
	ON_COMMAND(ID_ACTION_LISTEN, OnActionListen)
	ON_UPDATE_COMMAND_UI(ID_ACTION_LISTEN, OnUpdateActionListen)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_REMOTE_SERVER, OnFieldchangedIpaddressRemoteServer)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiView construction/destruction

CVmsnettomidiView::CVmsnettomidiView()
	: CFormView(CVmsnettomidiView::IDD)
{
   m_ppoint = new NetToMidiPoint;
	//{{AFX_DATA_INIT(CVmsnettomidiView)
	m_uiLocalServerPort = 0;
	m_uiRemoteServerPort = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CVmsnettomidiView::~CVmsnettomidiView()
{
   if(m_ppoint != NULL)
   {
      delete m_ppoint;
   }
}

void CVmsnettomidiView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVmsnettomidiView)
	DDX_Control(pDX, IDC_IPADDRESS_REMOTE_SERVER, m_ipaddressRemoteServer);
	DDX_Text(pDX, IDC_EDIT_LOCAL_SERVER_PORT, m_uiLocalServerPort);
	DDX_Text(pDX, IDC_EDIT_REMOTE_SERVER_PORT, m_uiRemoteServerPort);
	//}}AFX_DATA_MAP
}

BOOL CVmsnettomidiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CVmsnettomidiView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

   CString str;
   str = AfxGetApp()->GetProfileString("TCP Settings", "IP Address", "127.0.0.1");
   SetAddress(m_ipaddressRemoteServer, str);	
   m_uiLocalServerPort = AfxGetApp()->GetProfileInt("TCP Settings", "Local Server Port", 8734);
   m_uiRemoteServerPort = AfxGetApp()->GetProfileInt("TCP Settings", "Remote Server Port", 8734);
   UpdateData(FALSE);

}

/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiView printing

BOOL CVmsnettomidiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CVmsnettomidiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVmsnettomidiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CVmsnettomidiView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiView diagnostics

#ifdef _DEBUG
void CVmsnettomidiView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVmsnettomidiView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVmsnettomidiDoc* CVmsnettomidiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVmsnettomidiDoc)));
	return (CVmsnettomidiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVmsnettomidiView message handlers


void CVmsnettomidiView::OnActionStop() 
{
   Stop();
}


bool CVmsnettomidiView::Listen()
{
   ASSERT(m_ppoint->GetState() == _vmsnettomidi::StateInitial);
   if(m_ppoint->GetState() != _vmsnettomidi::StateInitial)
      return false;

   m_ppoint->PulseEvent(_vmsnettomidi::EventListen);

   return true;
}

void CVmsnettomidiView::Stop()
{
   ASSERT(m_ppoint->GetState() != _vmsnettomidi::StateInitial);
   if(m_ppoint->GetState() == _vmsnettomidi::StateInitial)
      return;

   m_ppoint->PulseEvent(_vmsnettomidi::EventEnd);

}

bool CVmsnettomidiView::Call()
{

   BYTE  b1, b2, b3, b4;
   m_ipaddressRemoteServer.GetAddress(b1, b2, b3, b4);
   CString str;
   str.Format("%d.%d.%d.%d", b1, b2, b3, b4);


   m_ppoint->m_strRemoteServerAddress = str;
   m_ppoint->m_uiRemoteServerPort = m_uiRemoteServerPort;

   ASSERT(m_ppoint->GetState() == _vmsnettomidi::StateInitial);
   if(m_ppoint->GetState() != _vmsnettomidi::StateInitial)
      return false;

   m_ppoint->PulseEvent(_vmsnettomidi::EventCall);

   return true;
}

void CVmsnettomidiView::OnChangeEditRemoteServerPort() 
{
   if(UpdateData())
   {
      AfxGetApp()->WriteProfileInt("TCP Settings", "Remote Server Port", m_uiRemoteServerPort);
   }
}

void CVmsnettomidiView::OnChangeEditLocalServerPort() 
{
   if(UpdateData())
   {
      AfxGetApp()->WriteProfileInt("TCP Settings", "Local Server Port", m_uiLocalServerPort);
   }
}

void CVmsnettomidiView::OnActionCall() 
{
   Call();
}

void CVmsnettomidiView::OnUpdateActionCall(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_ppoint->GetState() == _vmsnettomidi::StateInitial);
}

void CVmsnettomidiView::OnActionListen() 
{
   m_ppoint->SetServerPort(m_uiLocalServerPort);
   Listen();
}

void CVmsnettomidiView::OnUpdateActionListen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_ppoint->GetState() == _vmsnettomidi::StateInitial);
}


void CVmsnettomidiView::OnUpdateActionStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_ppoint->GetState() != _vmsnettomidi::StateInitial);
}

void CVmsnettomidiView::OnFieldchangedIpaddressRemoteServer(NMHDR* pNMHDR, LRESULT* pResult) 
{
   CString str;
   GetAddress(m_ipaddressRemoteServer, str);	
   AfxGetApp()->WriteProfileString("TCP Settings", "IP Address", str);
	*pResult = 0;
}
