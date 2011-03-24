// _vmspDocumentManager.cpp: implementation of the DocumentManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DocumentManager.h"

#include "MainFrm.h"
#include "vmpLightDoc.h"
#include "DesktopView.h"
#include "IpFrame.h"


#include "PaneView1.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// {F53B78E0-A6F5-41CF-B4FB-9F9FE49DD416}
static const CLSID clsidMid =
{ 0xf53b78e0, 0xa6f5, 0x41cf, { 0xb4, 0xfb, 0x9f, 0x9f, 0xe4, 0x9d, 0xd4, 0x16 } };

// {F53B78E0-A6F5-41CF-B4FB-9F9FE49DD416}
static const CLSID clsidKar =
{ 0xf53b78e0, 0xa6f5, 0x41cf, { 0xb4, 0xfb, 0x9f, 0x9f, 0xe4, 0x9d, 0xd4, 0x17 } };

// {F53B78E0-A6F5-41CF-B4FB-9F9FE49DD416}
static const CLSID clsidSt3 =
{ 0xf53b78e0, 0xa6f5, 0x41cf, { 0xb4, 0xfb, 0x9f, 0x9f, 0xe4, 0x9d, 0xd4, 0x18 } };


namespace vmplite
{


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DocumentManager::DocumentManager()
{

}

DocumentManager::~DocumentManager()
{

}

bool DocumentManager::CreateTemplates()
{
   DesktopApp * papp = (DesktopApp *) AfxGetApp();

   // Connect the COleTemplateServer to the document template.
   //    The COleTemplateServer creates new documents on behalf
   //    of requesting OLE containers by using information
   //    specified in the document template.
//	m_serverMid.ConnectTemplate(clsidMid, playercentral.GetDocTemplate(), FALSE);
	//m_serverKar.ConnectTemplate(clsidKar, playercentral.GetDocTemplate(), FALSE);
	//m_serverSt3.ConnectTemplate(clsidSt3, playercentral.GetDocTemplate(), FALSE);

	// Register all OLE server factories as running.  This enables the
	//    OLE libraries to create objects from other applications.
//	m_serverMid.RegisterAll();
	//m_serverKar.RegisterAll();
	//m_serverSt3.RegisterAll();

//xxx	_Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);

   return true;
}
bool DocumentManager::UpdateRegistry()
{

//	m_serverMid.UpdateRegistry(OAT_DOC_OBJECT_SERVER, IDS_MID);

   return true;
}

void DocumentManager::CloseAllDocuments(BOOL bEndSession) // close documents before exiting
{
   DocManager::CloseAllDocuments(bEndSession);
}


////////////////////////////////////////////////
} // namespace _vmsp
////////////////////////////////////////////////


