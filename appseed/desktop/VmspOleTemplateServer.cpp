// VmspOleTemplateServer.cpp: implementation of the CVmspOleTemplateServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VmspOleTemplateServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVmspOleTemplateServer::CVmspOleTemplateServer()
{

}

CVmspOleTemplateServer::~CVmspOleTemplateServer()
{

}

void CVmspOleTemplateServer::UpdateRegistry(OLE_APPTYPE nAppType,
										UINT nIDDocString,
	LPCTSTR* rglpszRegister, LPCTSTR* rglpszOverwrite)
{
   AStrArray strarray;

	String str;

	str.LoadString(nIDDocString);

	strarray.AddTokens(str, "\n", true);


	ASSERT(m_pDocTemplate != NULL);
//	ASSERT(m_bOAT == (BYTE) OAT_UNKNOWN);
	m_bOAT = (BYTE) nAppType;

	// get registration info from doc template string
	String strServerName;
	String strLocalServerName;
	String strLocalShortName;
	String strLocalFilterName;
	String strLocalFilterExt;


	strServerName = strarray[CDocTemplate::regFileTypeId];
	if (strServerName.IsEmpty())
	{
		TRACE0("Error: not enough information in DocTemplate to register OLE server.\n");
		return;
	}
	strLocalServerName = strarray[CDocTemplate::regFileTypeName];
	if (strLocalServerName.IsEmpty())
		strLocalServerName = strServerName;     // use non-localized name
	strLocalShortName = strarray[CDocTemplate::fileNewName];
	if(strLocalShortName.IsEmpty())
		strLocalShortName = strLocalServerName; // use long name
	strLocalFilterName = strarray[CDocTemplate::filterName];
	if (strLocalFilterName.IsEmpty())
		ASSERT(nAppType != OAT_DOC_OBJECT_SERVER);
	strLocalFilterExt = strarray[CDocTemplate::filterExt];
	if (strLocalFilterExt.IsEmpty())
		ASSERT(nAppType != OAT_DOC_OBJECT_SERVER);


	ASSERT(strServerName.Find(' ') == -1);  // no spaces allowed

	int nIconIndex = 0;
	POSITION pos = AfxGetApp()->GetFirstDocTemplatePosition();
	for (int nIndex = 1; pos != NULL; nIndex++)
	{
		DocTemplate* pTemplate = (DocTemplate *) AfxGetApp()->GetNextDocTemplate(pos);
		if (pTemplate == m_pDocTemplate)
		{
			nIconIndex = nIndex;
			pos = NULL; // set exit condition
		}
	}

	// place entries in system registry
	if (!AfxOleRegisterServerClass(m_clsid, strServerName,
		strLocalShortName, strLocalServerName, nAppType,
		rglpszRegister, rglpszOverwrite, nIconIndex,
		strLocalFilterName, strLocalFilterExt))
	{
		// not fatal (don't fail just warn)
		AfxMessageBox(AFX_IDP_FAILED_TO_AUTO_REGISTER);
	}
}