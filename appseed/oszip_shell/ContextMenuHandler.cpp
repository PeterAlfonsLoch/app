// ContextMenuHandler.cpp : Implementation of CContextMenuHandler
#include "stdafx.h"
#include "Oszip_shell.h"
#include "ContextMenuHandler.h"

/////////////////////////////////////////////////////////////////////////////
// CContextMenuHandler

CContextMenuHandler::CContextMenuHandler()
{
}


STDMETHODIMP CContextMenuHandler::QueryContextMenu(HMENU hmenu, UINT uiIndexMenu, 
                                                   UINT uiFirstCmdId, UINT uiLastCmdId,
                                                   UINT uiFlags)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return S_OK;
}
