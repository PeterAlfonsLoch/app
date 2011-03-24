// LyricViewLineTemplates.h: interface for the CLyricViewLineTemplates class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LYRICVIEWLINETEMPLATES_H__31BE8220_8FAD_417A_86A8_813090ECD1BB__INCLUDED_)
#define AFX_LYRICVIEWLINETEMPLATES_H__31BE8220_8FAD_417A_86A8_813090ECD1BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseArray.h" 
#include "LyricViewLineTemplate.h" 

class CLyricViewLineTemplates  : public BaseArray< CLyricViewLineTemplate, CLyricViewLineTemplate &>
{
public:
	CLyricViewLineTemplates();
	virtual ~CLyricViewLineTemplates();
public:
    CXfplayerViewLines();
//    inline CLyricViewLineTemplate & ElementAt(int iIndex);
protected:
    int     m_iFirstVisible;
    int     m_iLastVisible;
public:
	void SetRenderWindow(base_wnd * pWnd);
//	void SetEffect(int iEffect);
//	void SetBackgroundDC(CDC * lpDC);
//	void SetForegroundDC(CDC * lpDC);
	void Prepare(CLyricViewLineTemplate * lpViewLine);
	void Prepare();
    
	//int GetFirstVisibleLineIndex();
    //int GetLastVisibleLineIndex();
//	void OnChildSetVisible(CLyricViewLineTemplate * lpViewLine, bool bVisible);
//	int GetAt(CLyricViewLineTemplate ** pViewLine, CXfplayerViewLines & viewLines, int iIndex);
//	int GetTokenLine(int iToken, CLyricViewLineTemplate ** viewLine);
	
   
};

#endif // !defined(AFX_LYRICVIEWLINETEMPLATES_H__31BE8220_8FAD_417A_86A8_813090ECD1BB__INCLUDED_)
