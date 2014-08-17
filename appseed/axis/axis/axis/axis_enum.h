#pragma once


template <class TYPE>
class axis_enum_names :
   public map < TYPE, TYPE, string, string >
{
public:

   typedef typename map < TYPE, TYPE, string, string >::pair BASE_ENUM_PAIR;

   axis_enum_names(BASE_ENUM_PAIR pairs[]);
};


template <class TYPE>
axis_enum_names < TYPE > ::axis_enum_names(BASE_ENUM_PAIR pairs[]) :
map < TYPE, TYPE, string, string >(pairs)
{
}

template < class TYPE, TYPE edefault = 0 >
class axis_enum
{
public:

   axis_enum();
   axis_enum(const axis_enum < TYPE, edefault> & evalue);
   axis_enum(TYPE evalue);
   axis_enum(int32_t i);
   virtual ~axis_enum();

   TYPE m_evalue;

   void DefaultConstruct();

   const axis_enum <TYPE, edefault> & operator = (int32_t i);

   const axis_enum <TYPE, edefault> & operator = (TYPE evalue);
   const axis_enum <TYPE, edefault> & operator &= (TYPE evalue);
   const axis_enum <TYPE, edefault> & operator |= (TYPE evalue);

   const axis_enum <TYPE, edefault> & operator = (const axis_enum < TYPE, edefault> & evalue);
   const axis_enum <TYPE, edefault> & operator &= (const axis_enum < TYPE, edefault> & evalue);
   const axis_enum <TYPE, edefault> & operator |= (const axis_enum < TYPE, edefault> & evalue);

   bool operator == (const axis_enum < TYPE, edefault> & evalue) const;
   bool operator == (TYPE evalue) const;

   operator TYPE() const;

   //string get_name();
   //void set_by_name(const char * psz);

};

template <class TYPE, TYPE edefault>
axis_enum<TYPE, edefault>::axis_enum()
{
   DefaultConstruct();
}

template <class TYPE, TYPE edefault>
axis_enum<TYPE, edefault>::axis_enum(const axis_enum < TYPE, edefault> & evalue)
{
   operator = (evalue);
}

template <class TYPE, TYPE edefault>
axis_enum<TYPE, edefault>::axis_enum(TYPE evalue)
{
   m_evalue = evalue;
}

template <class TYPE, TYPE edefault>
axis_enum<TYPE, edefault>::axis_enum(int32_t i)
{
   m_evalue = (TYPE) i;
}

template <class TYPE, TYPE edefault>
axis_enum<TYPE, edefault>::~axis_enum()
{
}

template <class TYPE, TYPE edefault>
void axis_enum<TYPE, edefault>::DefaultConstruct()
{
   m_evalue = edefault;
}

template <class TYPE, TYPE edefault>
const axis_enum<TYPE, edefault> & axis_enum<TYPE, edefault>::operator = (int32_t i)
{
   m_evalue = (TYPE) i;
   return *this;
}


template <class TYPE, TYPE edefault>
const axis_enum<TYPE, edefault> & axis_enum<TYPE, edefault>::operator = (TYPE evalue)
{
   m_evalue = evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
const axis_enum<TYPE, edefault> & axis_enum<TYPE, edefault>::operator &= (TYPE evalue)
{
   m_evalue = (TYPE) (m_evalue & evalue);
   return *this;
}

template <class TYPE, TYPE edefault>
const axis_enum<TYPE, edefault> & axis_enum<TYPE, edefault>::operator |= (TYPE evalue)
{
   m_evalue = (TYPE) (m_evalue | evalue);
   return *this;
}

template <class TYPE, TYPE edefault>
const axis_enum<TYPE, edefault> & axis_enum<TYPE, edefault>::operator = (const axis_enum < TYPE, edefault> & evalue)
{
   m_evalue = evalue.m_evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
const axis_enum<TYPE, edefault> & axis_enum<TYPE, edefault>::operator &= (const axis_enum < TYPE, edefault> & evalue)
{
   m_evalue &= evalue.m_evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
const axis_enum<TYPE, edefault> & axis_enum<TYPE, edefault>::operator |= (const axis_enum < TYPE, edefault> & evalue)
{
   m_evalue |= evalue.m_evalue;
   return *this;
}

template <class TYPE, TYPE edefault>
bool axis_enum<TYPE, edefault>::operator == (const axis_enum < TYPE, edefault> & evalue) const
{
   return m_evalue == evalue.m_evalue;
}

template <class TYPE, TYPE edefault>
bool axis_enum<TYPE, edefault>::operator == (TYPE evalue) const
{
   return m_evalue == evalue;
}

template <class TYPE, TYPE edefault>
axis_enum<TYPE, edefault>::operator TYPE () const
{
   return m_evalue;
}

/*template <class TYPE, TYPE edefault>
string
axis_enum<TYPE, edefault>::get_name()
{
   return get_name(m_evalue);
}

template <class TYPE, TYPE edefault>
void
axis_enum<TYPE, edefault>::
set_by_name(const char * psz)
{
   m_evalue = from_name(psz, edefault);
}*/

