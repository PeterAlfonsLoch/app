// AlbumThread.cpp : implementation file
//

#include "stdafx.h"
#include "vmplight.h"
#include "AlbumThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AlbumThread

IMPLEMENT_DYNCREATE(AlbumThread, CWinThread)

AlbumThread::AlbumThread()
{
}

AlbumThread::~AlbumThread()
{
}

BOOL AlbumThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int AlbumThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(AlbumThread, CWinThread)
	//{{AFX_MSG_MAP(AlbumThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AlbumThread message handlers
