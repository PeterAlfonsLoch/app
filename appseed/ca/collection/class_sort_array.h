#pragma once


template <class BASE_CLASS, class TYPE, class ARG_TYPE, class BASE_ARRAY = raw_array < TYPE, ARG_TYPE > >
class class_sort_array :
	public BASE_ARRAY
{
public:

   bool SortFind(int (TYPE::* lpfnIntSortProperty)(), ARG_TYPE t, index & iIndex);
   void SortInsert(int (TYPE::* lpfnIntSortProperty)(), ARG_TYPE t);

   virtual void QuickSort(
      TYPE & (BASE_CLASS:: * lpfnGet)(index),
		index (* lpfnCompare)(TYPE &, TYPE &),
      void (BASE_CLASS::* lpfnSwap)(index, index));

   virtual void QuickSort(
      TYPE & (BASE_CLASS:: * lpfnGet)(index),
		index (* lpfnCompare)(void *, TYPE &, TYPE &),
      void (BASE_CLASS::* lpfnSwap)(index, index),
      void * pvoid);
};

template < class BASE_CLASS, class TYPE, class ARG_TYPE, class BASE_ARRAY >
bool
class_sort_array < BASE_CLASS, TYPE, ARG_TYPE, BASE_ARRAY >::
SortFind(int (TYPE::* lpfnIntSortProperty)(), ARG_TYPE t, index & iIndex)
{
   if(this->get_size() == 0)
	{
		return false;
	}
   int iIntProperty = (((TYPE &)t).*lpfnIntSortProperty)();
	index iLBound = iIndex;
	index iUBound = this->get_size() - 1;
	int iCompare;
	while(true)
	{
		iIndex = (iUBound + iLBound) / 2;
		iCompare = (this->element_at(iIndex).*lpfnIntSortProperty)() - iIntProperty;
		if(iCompare == 0)
		{
			return true;
		}
		else if(iCompare > 0)
		{
			iUBound = iIndex - 1;
		}
		else
		{
			iLBound = iIndex + 1;
		}
		if(iUBound < iLBound)
			break;

	}
	return false;

}

template < class BASE_CLASS, class TYPE, class ARG_TYPE, class BASE_ARRAY >
void
class_sort_array < BASE_CLASS, TYPE, ARG_TYPE, BASE_ARRAY >::
SortInsert(int (TYPE::* lpfnIntSortProperty)(), ARG_TYPE t)
{
	int iIndex = 0;
	SortFind(lpfnIntSortProperty, t, iIndex);
	insert_at(iIndex, t);
}

template < class BASE_CLASS, class TYPE, class ARG_TYPE, class BASE_ARRAY >
void
class_sort_array < BASE_CLASS, TYPE, ARG_TYPE, BASE_ARRAY >::
QuickSort(
	TYPE & (BASE_CLASS:: * lpfnGet)(index),
	index (* lpfnCompare)(TYPE &, TYPE &),
   void (BASE_CLASS::* lpfnSwap)(index, index))
{
		index_array stackLowerBound;
		index_array stackUpperBound;
		index iLowerBound;
		index iUpperBound;
		index iLPos, iUPos, iMPos;
	//	TYPE t;

		if(this->get_size() >= 2)
		{
			stackLowerBound.push(0);
			stackUpperBound.push(this->get_size() - 1);
			while(true)
			{
				iLowerBound = stackLowerBound.pop();
				iUpperBound = stackUpperBound.pop();
				iLPos = iLowerBound;
				iMPos = iLowerBound;
				iUPos = iUpperBound;
				while(true)
				{
					while(true)
					{
						if(iMPos == iUPos)
							break;
						if(lpfnCompare((((BASE_CLASS *) this)->*lpfnGet)(iMPos), (((BASE_CLASS *) this)->*lpfnGet)(iUPos)) <= 0)
							iUPos--;
						else
						{
							(((BASE_CLASS *) this)->*lpfnSwap)(iMPos, iUPos);
							break;
						}
					}
					if(iMPos == iUPos)
						break;
					iMPos = iUPos;
					while(true)
					{
						if(iMPos == iLPos)
							break;
						if(lpfnCompare((((BASE_CLASS *) this)->*lpfnGet)(iLPos), (((BASE_CLASS *) this)->*lpfnGet)(iMPos)) <= 0)
							iLPos++;
						else
						{
							(((BASE_CLASS *) this)->*lpfnSwap)(iLPos, iMPos);
							break;
						}
					}
					if(iMPos == iLPos)
						break;
					iMPos = iLPos;
				}
				if(iLowerBound < iMPos - 1)
				{
					stackLowerBound.push(iLowerBound);
					stackUpperBound.push(iMPos - 1);
				}
				if(iMPos + 1 < iUpperBound)
				{
					stackLowerBound.push(iMPos + 1);
					stackUpperBound.push(iUpperBound);
				}
				if(stackLowerBound.get_size() == 0)
					break;
			}
		}
	}

template < class BASE_CLASS, class TYPE, class ARG_TYPE, class BASE_ARRAY >
void
class_sort_array < BASE_CLASS, TYPE, ARG_TYPE, BASE_ARRAY >::
QuickSort(
	TYPE & (BASE_CLASS:: * lpfnGet)(index),
	index (* lpfnCompare)(void * pvoid, TYPE &, TYPE &),
   void (BASE_CLASS::* lpfnSwap)(index, index),
   void * pvoid)
{
		index_array stackLowerBound;
		index_array stackUpperBound;
		index iLowerBound;
		index iUpperBound;
		index iLPos, iUPos, iMPos;
	//	TYPE t;

		if(this->get_size() >= 2)
		{
			stackLowerBound.push(0);
			stackUpperBound.push(this->get_size() - 1);
			while(true)
			{
				iLowerBound = stackLowerBound.pop();
				iUpperBound = stackUpperBound.pop();
				iLPos = iLowerBound;
				iMPos = iLowerBound;
				iUPos = iUpperBound;
				while(true)
				{
					while(true)
					{
						if(iMPos == iUPos)
							break;
						if(lpfnCompare(pvoid, (((BASE_CLASS *) this)->*lpfnGet)(iMPos), (((BASE_CLASS *) this)->*lpfnGet)(iUPos)) <= 0)
							iUPos--;
						else
						{
							(((BASE_CLASS *) this)->*lpfnSwap)(iMPos, iUPos);
							break;
						}
					}
					if(iMPos == iUPos)
						break;
					iMPos = iUPos;
					while(true)
					{
						if(iMPos == iLPos)
							break;
						if(lpfnCompare(pvoid, (((BASE_CLASS *) this)->*lpfnGet)(iLPos), (((BASE_CLASS *) this)->*lpfnGet)(iMPos)) <= 0)
							iLPos++;
						else
						{
							(((BASE_CLASS *) this)->*lpfnSwap)(iLPos, iMPos);
							break;
						}
					}
					if(iMPos == iLPos)
						break;
					iMPos = iLPos;
				}
				if(iLowerBound < iMPos - 1)
				{
					stackLowerBound.push(iLowerBound);
					stackUpperBound.push(iMPos - 1);
				}
				if(iMPos + 1 < iUpperBound)
				{
					stackLowerBound.push(iMPos + 1);
					stackUpperBound.push(iUpperBound);
				}
				if(stackLowerBound.get_size() == 0)
					break;
			}
		}
	}

