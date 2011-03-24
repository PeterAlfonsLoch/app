// FrameWndInterface.h: interface for the FrameWndInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSGENFRAMEWNDINTERFACE_H__79D55281_0D81_44DA_AFE8_701E4BF6FA81__INCLUDED_)
#define AFX__VMSGENFRAMEWNDINTERFACE_H__79D55281_0D81_44DA_AFE8_701E4BF6FA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OleFrameHook;

namespace _vmswin
{

class CLASS_DECL_VMSWIN FrameWndInterface  
{
public:
	virtual HWND _GetSafeHwnd() = 0;
	FrameWndInterface();
	virtual ~FrameWndInterface();

   virtual OleFrameHook * GetNotifyHook();

};

}

#endif // !defined(AFX__VMSGENFRAMEWNDINTERFACE_H__79D55281_0D81_44DA_AFE8_701E4BF6FA81__INCLUDED_)
