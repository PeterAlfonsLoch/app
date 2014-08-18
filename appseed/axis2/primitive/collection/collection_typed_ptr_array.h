#pragma once

/*

class CLASS_DECL_AXIS ptr_array :
   virtual public comparable_raw_array < void * >::type
{
public:

   raw_index_array stackLowerBound;
   raw_index_array stackUpperBound;


   inline void quick_sort(void swap(void * lpVoidSwapArg, index iA, index iB), void * lpVoidSwapArg)
   {

      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;
      void * p;


      stackLowerBound.allocate(0, 256);
      stackUpperBound.allocate(0, 256);


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
                  if(this->m_pData[iMPos] <= this->m_pData[iUPos])
                     iUPos--;
                  else
                  {
                     p = this->m_pData[iMPos];
                     this->m_pData[iMPos] = this->m_pData[iUPos];
                     this->m_pData[iUPos] = p;
                     swap(lpVoidSwapArg, iUPos, iMPos);
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
                  if(this->m_pData[iLPos] <= this->m_pData[iMPos])
                     iLPos++;
                  else
                  {
                     p = this->m_pData[iMPos];
                     this->m_pData[iMPos] = this->m_pData[iUPos];
                     this->m_pData[iUPos] = p;
                     swap(lpVoidSwapArg, iLPos, iMPos);
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

   inline bool sort_find(void * p, index & iIndex, index iStart, index iEnd) const
   {
      if(this->get_size() == 0)
      {
         return false;
      }
      index iLowerBound = iStart;
      index iMaxBound = iEnd;
      index iUpperBound = iMaxBound;
      ::primitive::memory_offset iCompare;
      // do binary search
      iIndex = (iUpperBound + iLowerBound) / 2;
      while(iUpperBound - iLowerBound >= 8)
      {
         iCompare = (byte *) this->element_at(iIndex) - (byte *) p;
         if(iCompare == 0)
         {
            return true;
         }
         else if(iCompare > 0)
         {
            iUpperBound = iIndex - 1;
            if(iUpperBound < 0)
            {
               iIndex = 0;
               break;
            }
         }
         else
         {
            iLowerBound = iIndex + 1;
            if(iLowerBound > iMaxBound)
            {
               iIndex = iMaxBound + 1;
               break;
            }
         }
         iIndex = (iUpperBound + iLowerBound) / 2;
      }
      // do sequential search
      while(iIndex < this->get_count())
      {
         iCompare = (byte *) this->element_at(iIndex) - (byte *) p;
         if(iCompare == 0)
            return true;
         else if(iCompare < 0)
            iIndex++;
         else
            break;
      }
      if(iIndex >= this->get_count())
         return false;
      while(iIndex >= 0)
      {
         iCompare = (byte *) this->element_at(iIndex) - (byte *) p;
         if(iCompare == 0)
            return true;
         else if(iCompare > 0)
            iIndex--;
         else
            break;
      }
      iIndex++;
      return false;

   }


};




/////////////////////////////////////////////////////////////////////////////
// CTypedPtrArray<AXIS_CLASS, POINTER>

template < class POINTER, class AXIS_CLASS = ptr_array>
class typed_ptr_array :
   public AXIS_CLASS
{
public:
	// Accessing elements
	POINTER GetAt(int_ptr nIndex) const
		{ return (POINTER)AXIS_CLASS::GetAt(nIndex); }
	POINTER& ElementAt(int_ptr nIndex)
		{ return (POINTER&)AXIS_CLASS::ElementAt(nIndex); }
	void SetAt(int_ptr nIndex, POINTER ptr)
		{ AXIS_CLASS::SetAt(nIndex, ptr); }

	// Potentially growing the array
	void SetAtGrow(int_ptr nIndex, POINTER newElement)
		{ AXIS_CLASS::SetAtGrow(nIndex, newElement); }
	int_ptr add(POINTER newElement)
		{ return AXIS_CLASS::add(newElement); }
	int_ptr Append(const typed_ptr_array<POINTER, AXIS_CLASS>& src)
		{ return AXIS_CLASS::Append(src); }
	void Copy(const typed_ptr_array<POINTER, AXIS_CLASS>& src)
		{ AXIS_CLASS::Copy(src); }

	// Operations that move elements around
	void InsertAt(int_ptr nIndex, POINTER newElement, int_ptr nCount = 1)
		{ AXIS_CLASS::InsertAt(nIndex, newElement, nCount); }
	void InsertAt(int_ptr nStartIndex, typed_ptr_array<AXIS_CLASS, POINTER>* pNewArray)
		{ AXIS_CLASS::InsertAt(nStartIndex, pNewArray); }

	// overloaded operator helpers
	POINTER operator[](int_ptr nIndex) const
		{ return (POINTER)AXIS_CLASS::operator[](nIndex); }
	POINTER& operator[](int_ptr nIndex)
		{ return (POINTER&)AXIS_CLASS::operator[](nIndex); }
};



*/
