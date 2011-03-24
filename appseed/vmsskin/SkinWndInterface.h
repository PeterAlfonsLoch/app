// SkinWndInterface.h: interface for the SkinWndInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINWNDINTERFACE_H__7C30F679_6C4F_4621_9C82_BE632B50C431__INCLUDED_)
#define AFX_SKINWNDINTERFACE_H__7C30F679_6C4F_4621_9C82_BE632B50C431__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SkinWndInterface  
{
public:
	virtual void _001OnDraw(CDC * pdc);
	SkinWndInterface();
	virtual ~SkinWndInterface();

};

#endif // !defined(AFX_SKINWNDINTERFACE_H__7C30F679_6C4F_4621_9C82_BE632B50C431__INCLUDED_)
