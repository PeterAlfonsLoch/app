// XfplayerMultiDocTemplate.cpp: implementation of the CXfplayerMultiDocTemplate class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "../vms/Vms.h"
#include "MSMultiDocTemplate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//IMPLEMENT_DYNAMIC(CMSMultiDocTemplate, MultipleDocumentTemplate)

CMSMultiDocTemplate::CMSMultiDocTemplate(::ca::application * papp, UINT nIDResource, const type_info* pDocClass,
		const type_info* pFrameClass, const type_info* pViewClass)
        : BaseMultipleDocumentTemplate(papp, nIDResource, pDocClass, pFrameClass, pViewClass),
        DocumentTemplate(nIDResource, pDocClass, pFrameClass, pViewClass),
      BaseDocumentTemplate(papp, nIDResource, pDocClass, pFrameClass, pViewClass),
      MultipleDocumentTemplate(nIDResource, pDocClass, pFrameClass, pViewClass)
{
}
//CXfplayerMultiDocTemplate::CXfplayerMultiDocTemplate()
//{

//}

//CXfplayerMultiDocTemplate::~CXfplayerMultiDocTemplate()
//{

//}
