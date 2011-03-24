// Memory.h: interface for the CMemory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORY_H__88A14276_E83B_4B8E_B62A_4CE7A410A784__INCLUDED_)
#define AFX_MEMORY_H__88A14276_E83B_4B8E_B62A_4CE7A410A784__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemory  
{
public:
	CMemory();
	virtual ~CMemory();
	//static void freePointer(void * & pointer);
	

};
template<class TYPE> static void freePointer(TYPE * * pointer);
//template<class TYPE> void CMemory::freePointer(TYPE * * pointer)
template<class TYPE> void freePointer(TYPE * * pointer)
{
	free((void *) *pointer);
	*pointer = NULL;
}

#endif // !defined(AFX_MEMORY_H__88A14276_E83B_4B8E_B62A_4CE7A410A784__INCLUDED_)
