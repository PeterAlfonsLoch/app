#include "stdafx.h"

IMPLEMENT_DYNCREATE(MusicalPlayerLightDoc, OleServerDoc)

BEGIN_MESSAGE_MAP(MusicalPlayerLightDoc, OleServerDoc)
	//{{AFX_MSG_MAP(MusicalPlayerLightDoc)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(MusicalPlayerLightDoc, OleServerDoc)
	//{{AFX_DISPATCH_MAP(MusicalPlayerLightDoc)
   DISP_FUNCTION(MusicalPlayerLightDoc, "OpenFile", OpenFile, VT_BOOL, VTS_BSTR VTS_BOOL)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IVmpLight to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {12315345-A9D5-465F-9A0A-F208006E282D}
static const IID IID_IVmpLight =
{ 0x12315345, 0xa9d5, 0x465f, { 0x9a, 0xa, 0xf2, 0x8, 0x0, 0x6e, 0x28, 0x2d } };

BEGIN_INTERFACE_MAP(MusicalPlayerLightDoc, OleServerDoc)
	INTERFACE_PART(MusicalPlayerLightDoc, IID_IVmpLight, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightDoc construction/destruction

MusicalPlayerLightDoc::MusicalPlayerLightDoc()
{

	EnableAutomation();

	AfxOleLockApp();

   m_bPlay = false;

}

MusicalPlayerLightDoc::~MusicalPlayerLightDoc()
{
	AfxOleUnlockApp();
}

BOOL MusicalPlayerLightDoc::OnNewDocument()
{
	if (!OleServerDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightDoc server implementation

OleServerItem* MusicalPlayerLightDoc::OnGetEmbeddedItem()
{
	// OnGetEmbeddedItem is called by the framework to get the COleServerItem
	//  that is associated with the document.  It is only called when necessary.
   MusicalPlayerLightServerItem * pItem = new MusicalPlayerLightServerItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}



/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightDoc serialization

void MusicalPlayerLightDoc::Serialize(CArchive& ar)
{
   MMRESULT mmr;
   if (ar.IsStoring())
   {
   }
   else
   {
   }
}

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightDoc diagnostics

#ifdef _DEBUG
void MusicalPlayerLightDoc::AssertValid() const
{
	OleServerDoc::AssertValid();
}

void MusicalPlayerLightDoc::Dump(CDumpContext& dc) const
{
	OleServerDoc::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MusicalPlayerLightDoc commands


CWinThread * MusicalPlayerLightDoc::HelperGetMidiPlayerCallbackThread()
{
   return &gen::ThreadContainer::AppGetHighThread();
}



BOOL MusicalPlayerLightDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{

   DeleteContents();



   UpdateAllViews(NULL, 1000, 0);
	
	return TRUE;
}

void MusicalPlayerLightDoc::DeleteContents() 
{
	OleServerDoc::DeleteContents();
}



BOOL MusicalPlayerLightDoc::OpenFile(LPCTSTR bstrFilePath, BOOL bMakeVisible) 
{
   String str;
   str = bstrFilePath;
   return AfxGetApp()->OpenDocumentFile(str) != NULL;
}


EPaneView MusicalPlayerLightDoc::GetViewId()
{
   PaneViewUpdateHint uh;

   uh.m_eview = PaneViewNone;
   uh.SetType(PaneViewUpdateHint::TypeGetView);
   UpdateAllViews(NULL, 0, &uh);
   return uh.m_eview;

}


PaneView * MusicalPlayerLightDoc::GetPaneView()
{
   POSITION pos = GetFirstViewPosition();
   while(pos != NULL)
   {
      BaseView * pview = GetNextView(pos);
      if(pview->IsKindOf(RUNTIME_CLASS(PaneView)))
      {
         return (PaneView *) pview;
      }
   }
   return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// OleServerDoc::CPersistStorage

/*STDMETHODIMP_(ULONG) MusicalPlayerLightDoc::XViewObject::AddRef()
{
	METHOD_PROLOGUE_EX_(MusicalPlayerLightDoc, ViewObject)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) MusicalPlayerLightDoc::XViewObject::Release()
{
	METHOD_PROLOGUE_EX_(MusicalPlayerLightDoc, ViewObject)
	return pThis->ExternalRelease();
}

STDMETHODIMP MusicalPlayerLightDoc::XViewObject::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(MusicalPlayerLightDoc, ViewObject)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP MusicalPlayerLightDoc::XViewObject::Draw(
  DWORD dwAspect,   //Aspect to be drawn
  LONG lindex,      //Part of the object of interest in the draw 
                    //operation
  void * pvAspect,  //Pointer to DVASPECTINFO structure or NULL
  DVTARGETDEVICE * ptd,
                    //Pointer to target device in a structure
  HDC hicTargetDev, //Information context for the target device
  HDC hdcDraw,      //Device context on which to draw
  const LPRECTL lprcBounds,
                    //Pointer to the rectangle in which the object 
                    //is drawn
  const LPRECTL lprcWBounds,
                    //Pointer to the window extent and window origin 
                    //when drawing a metafile
  BOOL (*) (DWORD) pfnContinue,
                    //Pointer to the callback function for canceling 
                    //or continuing the drawing
  DWORD dwContinue  //Value to pass to the callback function
)
{
	METHOD_PROLOGUE_EX_(MusicalPlayerLightDoc, ViewObject)
   return S_OK;
}

STDMETHODIMP MusicalPlayerLightDoc::XViewObject::GetColorSet(
  DWORD dwAspect,   //How the object is to be represented
  LONG lindex,      //Part of the object of interest in the draw 
                    //operation
  void * pvAspect,  //Always NULL
  DVTARGETDEVICE * ptd,
                    //Pointer to target device in a structure
  HDC hicTargetDev, //Information context for the target device
  LOGPALETTE ** ppColorSet
                    //Address of output variable that receives a 
                    //pointer to the requested LOGPALETTE structure
)
{
	METHOD_PROLOGUE_EX_(MusicalPlayerLightDoc, ViewObject)
   return S_OK;
}

STDMETHODIMP MusicalPlayerLightDoc::XViewObject::HRESULT Freeze(
  DWORD dwAspect,   //How the object is to be represented
  LONG lindex,      //Part of the object of interest in the draw 
                    //operation
  void * pvAspect,  //Always NULL
  DWORD * pdwFreeze //Points to location containing an identifying 
                    //key
)
{
	METHOD_PROLOGUE_EX_(MusicalPlayerLightDoc, ViewObject)
   return S_OK;
}

STDMETHODIMP MusicalPlayerLightDoc::XViewObject::UnFreeze(
 DWORD dwFreeze  //Contains key that determines view object to 
                  //unfreeze
)
{
	METHOD_PROLOGUE_EX_(MusicalPlayerLightDoc, ViewObject)
   return S_OK;
}

STDMETHODIMP MusicalPlayerLightDoc::XViewObject::SetAdvise(
  DWORD dwAspect,  //View for which notification is being requested
  DWORD advf,      //Information about the advise sink
  IAdviseSink * pAdvSink
                   //Pointer to the advise sink that is to receive 
                   //change notifications
)
{
	METHOD_PROLOGUE_EX_(MusicalPlayerLightDoc, ViewObject)
   return S_OK;
}


STDMETHODIMP MusicalPlayerLightDoc::XViewObject::GetAdvise(
  DWORD * pdwAspect,  //Pointer to where dwAspect parameter from 
                      //previous SetAdvise call is returned
  DWORD * padvf,      //Pointer to where advf parameter from 
                      //previous SetAdvise call is returned
  IAdviseSink ** ppAdvSink
                      //Address of output variable that receives the 
                      //IAdviseSink interface pointer
)
{
	METHOD_PROLOGUE_EX_(MusicalPlayerLightDoc, ViewObject)
   return S_OK;
}*/

DocObjectServer* MusicalPlayerLightDoc::GetDocObjectServer(LPOLEDOCUMENTSITE pDocSite)
{
	return new DocObjectServer(this, pDocSite);
}
