#pragma once



template < class TYPE, class ARG_TYPE = TYPE const &, class ARRAY_TYPE = comparable_eq_array < TYPE, ARG_TYPE > >
class comparable_array :
   virtual public ARRAY_TYPE
{
public:
   comparable_array();
   comparable_array(const comparable_array & array);

   void quick_sort(bool bAsc = true);


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



template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
comparable_array()
{
}
template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
comparable_array(const comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & a) :
ARRAY_TYPE(a)
{
   this->operator = (a);
}


class CLASS_DECL_BASE const_char_ptra :
   public comparable_array < const char * >
{
};


template < class TYPE, class ARRAY_TYPE = comparable_array < TYPE * > >
class ptr_array :
   virtual public ARRAY_TYPE
{
public:


   ptr_array();
   ptr_array(const ptr_array & array);

};






template < class TYPE, class ARRAY_TYPE >
ptr_array<  TYPE,  ARRAY_TYPE>::
ptr_array()
{
}

template < class TYPE, class ARRAY_TYPE >
ptr_array<  TYPE,  ARRAY_TYPE>::
ptr_array(const ptr_array<  TYPE, ARRAY_TYPE> & a) :
ARRAY_TYPE(a)
{
   this->operator = (a);
}
