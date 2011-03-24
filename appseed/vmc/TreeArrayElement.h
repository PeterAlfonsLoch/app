// TreeArrayElement.h: interface for the CTreeArrayElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREEARRAYELEMENT_H__3D5E027A_A4F8_428B_8B81_C7A5011357B7__INCLUDED_)
#define AFX_TREEARRAYELEMENT_H__3D5E027A_A4F8_428B_8B81_C7A5011357B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTreeArrayElement  
{
public:
//	CTreeArrayElement();
//	virtual ~CTreeArrayElement();
    virtual void OnArrayReallocation(void *pNewPointer) = 0;

};

#endif // !defined(AFX_TREEARRAYELEMENT_H__3D5E027A_A4F8_428B_8B81_C7A5011357B7__INCLUDED_)
