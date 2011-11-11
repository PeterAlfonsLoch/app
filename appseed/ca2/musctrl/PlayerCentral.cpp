// PlayerCentral.cpp: implementation of the CPlayerCentral class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Resource.h"

// Player
#include "KaraokeSDIFrame.h"
#include "PlayerCentral.h"
#include "PlayerCentralContainer.h"
#include "XfplayerDoc.h"
#include "XfplayerIPFrame.h"
#include "XfplayerView.h"
#include "XfplayerSingleDocTemplate.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPlayerCentral::CPlayerCentral()
{
    m_pdoctemplateMid = NULL;
	m_pdoctemplateKar = NULL;
	m_pdoctemplateSt3 = NULL;

}

CPlayerCentral::~CPlayerCentral()
{

}

CPlayerCentral & CPlayerCentral::AppGetPlayerCentral()
{
	return CPlayerCentralContainer::AppGetPlayerCentral();	
}

CXfplayerSingleDocTemplate * CPlayerCentral::GetDocTemplate()
{
    return m_pdoctemplateMid;
}


CXfplayerSingleDocTemplate * CPlayerCentral::CreateDocTemplate()
{
	if(m_pdoctemplateMid != NULL)
		return m_pdoctemplateMid;
	CXfplayerSingleDocTemplate* pdoctemplate;
	pdoctemplate = new CXfplayerSingleDocTemplate(
		IDR_SONG,
		RUNTIME_CLASS(CXfplayerDoc),
		RUNTIME_CLASS(CKaraokeSDIFrame),       // main SDI frame window
		RUNTIME_CLASS(CXfplayerView));
	m_pdoctemplateMid = pdoctemplate;
	pdoctemplate->SetServerInfo(
		IDR_XFPLAYER_SERVER_EMBEDDING, IDR_XFPLAYER_SERVER_INPLACE,
		RUNTIME_CLASS(CXfplayerIPFrame));
	
	return pdoctemplate;
}