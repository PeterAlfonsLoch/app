// VmspDll.h: interface for the CVmspDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VMSPDLL_H__27B2001A_AA6C_47CC_B43F_F849E9AA9C9F__INCLUDED_)
#define AFX_VMSPDLL_H__27B2001A_AA6C_47CC_B43F_F849E9AA9C9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVmspDll  
{
    static CVmspDll * g_pvmspdll;
public:
	CVmspDll();
	virtual ~CVmspDll();

    HINSTANCE m_hinstance;
    
    static CVmspDll * GetVmspDll();
    static void SetVmspDll( CVmspDll * pvmspdll);
};

#endif // !defined(AFX_VMSPDLL_H__27B2001A_AA6C_47CC_B43F_F849E9AA9C9F__INCLUDED_)
