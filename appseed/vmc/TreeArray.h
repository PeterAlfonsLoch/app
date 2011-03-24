#pragma once

#include "TreeArrayElement.h"

template <class TYPE, class ARG_TYPE>
class CTreeArray
: public BaseArray<TYPE, ARG_TYPE>
{
public:
	CTreeArray();
	virtual ~CTreeArray();
    void SetSize(int nNewSize, int nGrowBy  = -1);
    void OnReallocation();
};

template<class TYPE, class ARG_TYPE>
CTreeArray<TYPE, ARG_TYPE>::CTreeArray()
: BaseArray<TYPE, ARG_TYPE>()
{
}

template<class TYPE, class ARG_TYPE>
CTreeArray<TYPE, ARG_TYPE>::~CTreeArray()
{
    BaseArray<TYPE, ARG_TYPE>::~BaseArray<TYPE, ARG_TYPE>();
}

template<class TYPE, class ARG_TYPE>
void CTreeArray<TYPE, ARG_TYPE>::SetSize(int nNewSize, int nGrowBy)
{
    BaseArray<TYPE, ARG_TYPE>::SetSize(nNewSize, nGrowBy);
    OnReallocation();
}

template<class TYPE, class ARG_TYPE>
void CTreeArray<TYPE, ARG_TYPE>::OnReallocation()
{
    for(int i = 0; i < GetSize(); i++)
    {
        TYPE * pElement = &ElementAt(i);
        pElement->OnArrayReallocation(pElement);
    }
}

