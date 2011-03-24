// VmspOleTemplateServer.h: interface for the CVmspOleTemplateServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSPOLETEMPLATESERVER_H__512C50E4_67C3_4157_8D4C_6728D5C9BEAA__INCLUDED_)
#define AFX_VMSPOLETEMPLATESERVER_H__512C50E4_67C3_4157_8D4C_6728D5C9BEAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "msole/OleTemplateServer.h"


class CVmspOleTemplateServer : public OleTemplateServer  
{
public:
	CVmspOleTemplateServer();
	virtual ~CVmspOleTemplateServer();

	void UpdateRegistry(
		OLE_APPTYPE nAppType,
		UINT nIDDocString,
		LPCTSTR* rglpszRegister = NULL, LPCTSTR* rglpszOverwrite = NULL);

};

#endif // !defined(AFX_VMSPOLETEMPLATESERVER_H__512C50E4_67C3_4157_8D4C_6728D5C9BEAA__INCLUDED_)
