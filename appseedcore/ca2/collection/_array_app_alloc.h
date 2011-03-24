#pragma once

template <class TYPE, class ARG_TYPE>
class array_app_alloc :
   public array_ptr < TYPE, ARG_TYPE >
{
public:
   array_app_alloc(::ca::application * papp);
	array_app_alloc();
   array_app_alloc(const array_app_alloc & a);
	virtual ~array_app_alloc();

   virtual TYPE * add_new();
   void add(const TYPE & t);
   void add(TYPE * p);
   inline void insert_at(int iIndex, ARG_TYPE t);

   void remove_at(index iIndex);
   count remove_all(bool bDelete = true);
   void remove_last(bool bDelete = true);

   void copy(const array_app_alloc < TYPE, ARG_TYPE > & base_array);

   void set_size(int iSize);

	array_app_alloc < TYPE, ARG_TYPE > & operator = (const array_app_alloc <TYPE, ARG_TYPE> & base_array);

};

template <class TYPE, class ARG_TYPE>
array_app_alloc < TYPE, ARG_TYPE >::array_app_alloc(::ca::application * papp) :
   ca(papp)
{
}

template <class TYPE, class ARG_TYPE>
array_app_alloc < TYPE, ARG_TYPE >::array_app_alloc()
{
}

template <class TYPE, class ARG_TYPE>
array_app_alloc < TYPE, ARG_TYPE >::array_app_alloc(const array_app_alloc & a)
{
   operator = (a);
}

template <class TYPE, class ARG_TYPE>
array_app_alloc < TYPE, ARG_TYPE >::~array_app_alloc()
{
   remove_all();
}

template <class TYPE, class ARG_TYPE>
inline TYPE * array_app_alloc < TYPE, ARG_TYPE >::add_new()
{
   TYPE * pt = dynamic_cast < TYPE * > (Application.alloc(typeid(TYPE)));
   m_ptra.add(pt);
   return pt;
}


template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::add(
   const TYPE & t)
{
   TYPE * pt = dynamic_cast < TYPE * > (Application.alloc(typeid(TYPE)));
   *pt = t;
   m_ptra.add(pt);
}

template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::add(
   TYPE * p)
{
   array_ptr < TYPE, ARG_TYPE >::add(p);
}

template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::insert_at(
   int iIndex,
   ARG_TYPE t)
{
   TYPE * pt = dynamic_cast < TYPE * > (Application.alloc(typeid(TYPE)));
   *pt = t;
   m_ptra.insert_at(iIndex, pt);
}


template <class TYPE, class ARG_TYPE>
inline array_app_alloc <TYPE, ARG_TYPE> & array_app_alloc < TYPE, ARG_TYPE >::operator = (
   const array_app_alloc <TYPE, ARG_TYPE> & a)
{
	int i;
   for(i = 0; i < m_ptra.get_size(); i++)
   {
      element_at(i) = *a.m_ptra[i];
   }
   for(; i < a.m_ptra.get_size(); i++)
   {
      TYPE * pt = dynamic_cast < TYPE * > (Application.alloc(typeid(TYPE)));
      *pt = *a.m_ptra[i];
      m_ptra.add(pt);
   }
   m_ptra.set_size(a.m_ptra.get_size());
   return *this;
}


template <class TYPE, class ARG_TYPE>
void array_app_alloc < TYPE, ARG_TYPE >::copy(const array_app_alloc < TYPE, ARG_TYPE > & a)
{
   remove_all();
   for(int i = 0; i < a.get_size(); i++)
   {
      add(a[i]);
   }
}


template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::
set_size(int iSize)
{
   while(get_size() < iSize)
   {
      add(dynamic_cast < TYPE * > (Application.alloc(typeid(TYPE))));
   }
   while(get_size() > iSize)
   {
      remove_at(get_size() - 1);
   }
}


template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::remove_at(index iIndex)
{
   gen::del<TYPE>(m_ptra.element_at(iIndex));
   m_ptra.remove_at(iIndex);
}

template <class TYPE, class ARG_TYPE>
inline count array_app_alloc < TYPE, ARG_TYPE >::remove_all(bool bDelete /*=true*/)
{
   if(bDelete)
   {
      for(int iIndex = 0; iIndex < m_ptra.get_size(); iIndex++)
      {
         gen::del<TYPE>(m_ptra.element_at(iIndex));
      }
   }
   return m_ptra.remove_all();
}

template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::remove_last(bool bDelete /*=true*/)
{
   if(bDelete)
   {
      gen::del<TYPE>(m_ptra.last_element());
   }
   m_ptra.remove_last();
}
