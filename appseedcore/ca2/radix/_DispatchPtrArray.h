///////////////////////////////////////////////////////////////////////////////
//
// File Name: DispatchPtrArray.h
// Long Name: dispatch Pointer Array
//
// Author: Camilo Sasuke Tsumanuma
//
// Creation Date: 1999-2000
//
// Purpose: Base array that implements
//          array objects member functions calls.
//
///////////////////////////////////////////////////////////////////////////////
// DispatchPtrArray.h: interface for the DispatchPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

template <class TYPE, class TYPEPTR>
class DispatchPtrArray :
	public comparable_array<TYPEPTR, TYPEPTR>
{
public:
	DispatchPtrArray();
	virtual ~DispatchPtrArray();
   
   void PtrCallAll(void (TYPE::* lpfn)());
   void PtrCallAll(void (TYPE::* lpfn)(int), int i);
   void PtrCallAll(void (TYPE::* lpfn)(int, int), int i1, int i2);

};

template<class TYPE, class TYPEPTR>
DispatchPtrArray<TYPE, TYPEPTR>::DispatchPtrArray()
{
}

template<class TYPE, class TYPEPTR>
DispatchPtrArray<TYPE, TYPEPTR>::~DispatchPtrArray()
{
}

template <class TYPE, class TYPEPTR>
void
DispatchPtrArray<TYPE, TYPEPTR>::
PtrCallAll(void (TYPE::* lpfn)())
{
	for(int i = 0; i < get_size(); i++)
	{
		(element_at(i)->*lpfn)();
	}
}

template <class TYPE, class TYPEPTR>
void
DispatchPtrArray<TYPE, TYPEPTR>::
PtrCallAll(void (TYPE::* lpfn)(int), int iParam)
{
	for(int i = 0; i < get_size(); i++)
	{
		(element_at(i)->*lpfn)(iParam);
	}
}

template <class TYPE, class TYPEPTR>
void
DispatchPtrArray<TYPE, TYPEPTR>::
PtrCallAll(void (TYPE::* lpfn)(int, int), int iParam1, int iParam2)
{
	for(int i = 0; i < get_size(); i++)
	{
		(element_at(i)->*lpfn)(iParam1, iParam2);
	}
}
