#pragma once


#include "aura/primitive/collection/collection_var_array.h"
#include "aura/primitive/primitive_property_set.h"
#include "aura/primitive/primitive_memory.h"


template < typename Type, typename RawType >
Type string_array < Type, RawType >::get_at(index nIndex) const
{
   if (nIndex < 0 || nIndex >= this->m_nSize)
      throw index_out_of_bounds(this->get_app());
   return get_data()[nIndex];
}

template < typename Type, typename RawType >
void string_array < Type, RawType >::set_at(index nIndex, const char * newElement)
{
   if (nIndex < 0 || nIndex >= this->m_nSize)
      throw index_out_of_bounds(this->get_app());
   get_data()[nIndex] = newElement;
}


template < typename Type, typename RawType >
void string_array < Type, RawType >::set_at(index nIndex, const Type & newElement)
{
   if (nIndex < 0 || nIndex >= this->m_nSize)
      throw index_out_of_bounds(this->get_app());
   get_data()[nIndex] = newElement;
}


template < typename Type, typename RawType >
Type & string_array < Type, RawType >::element_at(index nIndex)
{
   if (nIndex < 0 || nIndex >= this->m_nSize)
      throw index_out_of_bounds(this->get_app());
   return get_data()[nIndex];
}


template < typename Type, typename RawType >
const Type & string_array < Type, RawType >::element_at(index nIndex) const
{
   if (nIndex < 0 || nIndex >= this->m_nSize)
      throw index_out_of_bounds(this->get_app());
   return get_data()[nIndex];
}


template < typename Type, typename RawType >
void string_array < Type, RawType >::add(const var & var)
{
   if (var.is_empty())
   {
   }
   else if (var.get_type() == var::type_stra)
   {
      ::lemon::array::add(*this, var.stra());
   }
   else if (var.cast < string_array < Type, RawType > >() != NULL)
   {
      ::lemon::array::add(*this, *var.cast < string_array < Type, RawType > >());
   }
   else if (var.get_type() == var::type_vara)
   {
      for (int32_t i = 0; i < var.vara().get_count(); i++)
      {
         ::lemon::array::add(*this, var.vara()[i].get_string());
      }
   }
   else if (var.get_type() == var::type_inta)
   {
      for (int32_t i = 0; i < var.inta().get_count(); i++)
      {
         ::lemon::array::add(*this, ::str::from(var.inta()[i]));
      }
   }
   else if (var.get_type() == var::type_propset)
   {
      for (auto assoc : var.propset())
      {
         ::lemon::array::add(*this, assoc.get_value().get_string());
      }
   }
   else
   {
      ::lemon::array::add(*this, var.get_string());
   }
}


template < typename Type, typename RawType >
void string_array < Type, RawType >::add(const property & prop)
{
   add(prop.get_value());
}


template < class Type, class RawType >
string_array < Type, RawType >  & string_array < Type, RawType > ::operator = (var varSrc)
{
   this->remove_all();
   if (varSrc.get_type() == var::type_stra)
   {
      varSrc.get_array(*this);
   }
   else
   {
      if (varSrc.get_count() == 1)
      {
         add((Type)varSrc.get_string());
      }
      else if (varSrc.get_count() > 1)
      {
         varSrc.get_array(*this);
      }
   }
   return *this;
}





template < typename Type, typename RawType >
memory string_array < Type, RawType > ::GetFormatV004()
{

   strsize iTotalLength = 0;

   strsize i;

   for (i = 0; i < this->m_nSize; i++)
   {
      iTotalLength += this->element_at(i).get_length();
      iTotalLength++;
   }

   if (iTotalLength == 0)
   {
      iTotalLength = 2;
   }
   else
   {
      iTotalLength++;
   }

   memory mem;

   mem.allocate(iTotalLength * sizeof(char));

   char * lpsz = (char *)mem.get_data();

   memset(lpsz, 0x00, iTotalLength * sizeof(char));

   char * lpszN = lpsz;

   strsize iLength;

   for (i = 0; i < this->m_nSize; i++)
   {

      Type * pstr = &this->element_at(i);

      iLength = pstr->get_length();

#ifdef WINDOWS
      strcat_s(lpszN, iLength, *pstr);
#else
      strcat(lpszN, *pstr);
#endif

#ifdef WINDOWSEX
      iLength = _tcsnbcnt(lpszN, iLength);
#elif defined(METROWINDOW)
      iLength = wcsnbcnt(lpszN, iLength);
#else
      iLength = strlen(lpszN);
#endif

      lpszN = (char *)((LPBYTE)lpszN) + iLength + sizeof(char);

   }

   if (iTotalLength == 2)
   {
      memset(lpsz, 0x00, iTotalLength * sizeof(char));
   }
   else
   {
      memset(lpszN, 0x00, sizeof(char));
   }

   return mem;

}
