// ImageLoaderEventContainer.h: interface for the CImageLoaderEventContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGELOADEREVENTCONTAINER_H__DF3B06A7_492A_4D19_889F_05A219961F35__INCLUDED_)
#define AFX_IMAGELOADEREVENTCONTAINER_H__DF3B06A7_492A_4D19_889F_05A219961F35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImageLoaderEventContainer  
{
public:
//   virtual void OnImageLoaded(
//      VARIANT * pVarInfoHeader,
//      VARIANT * bmBits) = 0;
//   virtual void OnImageStretched(
//      VARIANT * pVarInfoHeader,
//      VARIANT * bmBits,
//      VARIANT * pVarUserData,
//      int cx,
//      int cy) = 0;
   virtual void OnImageLoaded(
      HBITMAP hBitmap) = 0;
   virtual void OnImageStretched(
      HBITMAP hBitmap,
      int cx,
      int cy,
      int iUserData) = 0;

};

#endif // !defined(AFX_IMAGELOADEREVENTCONTAINER_H__DF3B06A7_492A_4D19_889F_05A219961F35__INCLUDED_)
