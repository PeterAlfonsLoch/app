// VmspHelp.h: interface for the CVmspHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSPHELP_H__A6989CE1_4668_4F8A_AC04_7DCB4EF7AF68__INCLUDED_)
#define AFX_VMSPHELP_H__A6989CE1_4668_4F8A_AC04_7DCB4EF7AF68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HelpCentral.h"

namespace VmspHelp
{
	extern CHelpCentral::CCsRow rowaContextSensitive[];
}

class CVmspHelp  
{
public:
	CVmspHelp();
	virtual ~CVmspHelp();
	

};

#endif // !defined(AFX_VMSPHELP_H__A6989CE1_4668_4F8A_AC04_7DCB4EF7AF68__INCLUDED_)
