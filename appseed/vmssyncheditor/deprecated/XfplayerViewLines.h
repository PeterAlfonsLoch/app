// XfplayerViewLines.h: interface for the CXfplayerViewLines class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XFPLAYERVIEWLINES_H__AB62AE03_6431_4CF4_91DF_3F8CB12C9EA0__INCLUDED_)
#define AFX_XFPLAYERVIEWLINES_H__AB62AE03_6431_4CF4_91DF_3F8CB12C9EA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XfplayerViewLine.h"

class CTransparentWndInterface;

class CXfplayerViewLines : public CArray<CXfplayerViewLine, CXfplayerViewLine &>  
{
public:
    CXfplayerViewLines();
protected:
    int     m_iFirstVisible;
    int     m_iLastVisible;
public:
	void SetRenderWindow(CWnd * pWnd);
	void SetEffect(int iEffect);
   void SetTwi(CTransparentWndInterface * pTwi);
	void Prepare(CXfplayerViewLine * lpViewLine);
	void Prepare();
    
   int GetFirstVisibleLineIndex();
   int GetLastVisibleLineIndex();
   void OnChildSetVisible(CXfplayerViewLine * lpViewLine, bool bVisible);
	
	virtual ~CXfplayerViewLines();
    
};

//CXfplayerViewLine& CXfplayerViewLines::ElementAt(int iIndex)
//{
  //  return CArray<CXfplayerViewLine, CXfplayerViewLine &>::ElementAt(iIndex);
    
//}
#endif // !defined(AFX_XFPLAYERVIEWLINES_H__AB62AE03_6431_4CF4_91DF_3F8CB12C9EA0__INCLUDED_)
