// _vmspDocumentManager.h: interface for the CDocumentManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSPDOCUMENTMANAGER_H__B42BEA50_8D27_4E61_97AA_CEA99783E56D__INCLUDED_)
#define AFX__VMSPDOCUMENTMANAGER_H__B42BEA50_8D27_4E61_97AA_CEA99783E56D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VmspOleTemplateServer.h"

namespace vmplite
{

   class DocumentManager :
      public DocManager
   {
   public:
	   //CVmspOleTemplateServer m_serverMid;
	   //CVmspOleTemplateServer m_serverKar;
	   //CVmspOleTemplateServer m_serverSt3;

   public:
	   bool UpdateRegistry();
	   bool CreateTemplates();
	   DocumentManager();
	   virtual ~DocumentManager();

};

////////////////////////////////////////////////
} // namespace _vmsp
////////////////////////////////////////////////


#endif // !defined(AFX__VMSPDOCUMENTMANAGER_H__B42BEA50_8D27_4E61_97AA_CEA99783E56D__INCLUDED_)

