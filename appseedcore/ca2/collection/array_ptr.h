#pragma once


template <class TYPE, class ARG_TYPE = const TYPE &, class BASE_PTRA = comparable_array < TYPE * >>
class array_ptr :
   virtual public array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >
{
public:
   array_ptr();
   virtual ~array_ptr();

   void remove_at(INT_PTR iIndex);
   count remove_all(bool bDelete = true);
   void remove_last(bool bDelete = true);
   
};

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::array_ptr()
{
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::~array_ptr()
{
   remove_all();
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_at(
   index iIndex)
{
   gen::_sdel<TYPE>(m_ptra.element_at(iIndex));
   m_ptra.remove_at(iIndex);
}

template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline count array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_all(bool bDelete /*=true*/)
{
   if(bDelete)
   {
      for(int iIndex = 0; iIndex < m_ptra.get_size(); iIndex++)
      {
         gen::_sdel<TYPE>(m_ptra.element_at(iIndex));
      }
   }
   return m_ptra.remove_all();
}


template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline void array_ptr < TYPE, ARG_TYPE, BASE_PTRA >::remove_last(bool bDelete /*=true*/)
{
   if(bDelete)
   {
      gen::_sdel<TYPE>(m_ptra.last_element());
   }
   m_ptra.remove_last();
}


