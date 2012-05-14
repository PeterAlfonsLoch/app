#pragma once

#include "collection/_map.h"

template <class TYPE>
class base_enum_names :
   public ::collection::map < TYPE, TYPE, string, string >
{
public:
   base_enum_names(pair pairs[]);
};


template <class TYPE>
base_enum_names < TYPE > ::base_enum_names(pair pairs[]) :
::collection::map < TYPE, TYPE, string, string >(pairs) 
{
}

template <class TYPE, TYPE edefault = 0>
class base_enum
{
public:

   base_enum();
   base_enum(const base_enum < TYPE, edefault> & evalue);
   base_enum(TYPE evalue);
   base_enum(int i);
   virtual ~base_enum();

   TYPE m_evalue;

   void DefaultConstruct();

   const base_enum <TYPE, edefault> & operator = (int i);

   const base_enum <TYPE, edefault> & operator = (TYPE evalue);
   const base_enum <TYPE, edefault> & operator &= (TYPE evalue);
   const base_enum <TYPE, edefault> & operator |= (TYPE evalue);

   const base_enum <TYPE, edefault> & operator = (const base_enum < TYPE, edefault> & evalue);
   const base_enum <TYPE, edefault> & operator &= (const base_enum < TYPE, edefault> & evalue);
   const base_enum <TYPE, edefault> & operator |= (const base_enum < TYPE, edefault> & evalue);

   bool operator == (const base_enum < TYPE, edefault> & evalue) const;
   bool operator == (TYPE evalue) const;

   operator TYPE() const;

   string get_name(::ca::application * papp);
   void set_by_name(::ca::application * papp, const char * psz);
   static string get_name(::ca::application * papp, TYPE e_type);
   static TYPE from_name(::ca::application * papp, const char * psz);
   
};

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::base_enum()
{
   DefaultConstruct();
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::base_enum(const base_enum < TYPE, edefault> & evalue)
{
   operator = (evalue);
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::base_enum(TYPE evalue)
{
   m_evalue = evalue;
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::base_enum(int i)
{
   m_evalue = (TYPE) i;
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::~base_enum()
{
}

template <class TYPE, TYPE edefault>
void base_enum<TYPE, edefault>::DefaultConstruct()
{
   m_evalue = edefault;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator = (int i)
{
   m_evalue = (TYPE) i;
   return *this;
}


template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator = (TYPE evalue)
{
   m_evalue = evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator &= (TYPE evalue)
{
   m_evalue = (TYPE) (m_evalue & evalue);
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator |= (TYPE evalue)
{
   m_evalue = (TYPE) (m_evalue | evalue);
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator = (const base_enum < TYPE, edefault> & evalue)
{
   m_evalue = evalue.m_evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator &= (const base_enum < TYPE, edefault> & evalue)
{
   m_evalue &= evalue.m_evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
const base_enum<TYPE, edefault> & base_enum<TYPE, edefault>::operator |= (const base_enum < TYPE, edefault> & evalue)
{
   m_evalue |= evalue.m_evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
bool base_enum<TYPE, edefault>::operator == (const base_enum < TYPE, edefault> & evalue) const
{
   return m_evalue == evalue.m_evalue;
}

template <class TYPE, TYPE edefault>
bool base_enum<TYPE, edefault>::operator == (TYPE evalue) const
{
   return m_evalue == evalue;
}

template <class TYPE, TYPE edefault>
base_enum<TYPE, edefault>::operator TYPE () const
{
   return m_evalue;
}

template <class TYPE, TYPE edefault>
string 
base_enum<TYPE, edefault>::get_name(::ca::application * papp)
{
   return get_name(papp, m_evalue);
}

template <class TYPE, TYPE edefault>
void 
base_enum<TYPE, edefault>::
set_by_name(::ca::application * papp, const char * psz)
{
   m_evalue = from_name(papp, psz, edefault);
}

template <class TYPE, TYPE edefault>
string
base_enum<TYPE, edefault>::
get_name(::ca::application * papp, TYPE e_type)
{
   return dynamic_cast < bergedge_application * > (papp)->get_enum_name(typeid(TYPE), e_type);
}

template <class TYPE, TYPE edefault>
TYPE 
base_enum<TYPE, edefault>::
from_name(::ca::application * papp, const char * psz)
{
   return (TYPE) dynamic_cast < bergedge_application * > (papp)->enum_from_name(typeid(TYPE), psz, edefault);
}
