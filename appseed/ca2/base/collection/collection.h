#pragma once






#define new DEBUG_NEW


#ifdef DEBUG
#define TEMPLATE_TYPE_NEW new(__FILE__ + string(" - ") + typeid(TYPE).name(), __LINE__)
#else
#define TEMPLATE_TYPE_NEW new
#endif


class index_array;


#undef new


#define new TEMPLATE_TYPE_NEW


#ifndef __max
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif

#define ARRAY_MOVE_SEMANTICS(A) \
      \
   A(A && a) :  \
   ca(a.get_app()) \
   { \
    \
   m_nGrowBy      = a.m_nGrowBy; \
   m_pData        = a.m_pData; \
   m_nSize        = a.m_nSize; \
   m_nMaxSize     = a.m_nMaxSize; \
   \
   a.m_pData      = ::null(); \
   \
   } \
   \
   inline A & A::operator = (A && a)      \
   {                                      \
                                          \
      if(&a != this)                      \
      { \
         destroy(); \
         \
         m_nGrowBy      = a.m_nGrowBy; \
         m_pData        = a.m_pData; \
         m_nSize        = a.m_nSize; \
         m_nMaxSize     = a.m_nMaxSize; \
         \
         a.m_pData      = null(); \
         \
      } \
      \
   return *this; \
   \
   } 




// raw array is a special array and should be used with care
// it uses operations like memmove and memcopy to move objects and does not
// call constructors and destructors for the elements
// it is faster than the more generic arrays and is proper for use
// with strict structs and primitive data types

template < typename C >
class class_size
{
public:

   sp(C)          m_p;
   ::count        m_c;

   class_size(C * p) : m_p(p), m_c(-1) {}

   class_size(C * p, ::count c) : m_p(::null()), m_c(c) {}

   class_size(const class_size & size) : m_p(size.m_p), m_c(size.m_c) {}

   operator ::count ()
   {
      if(m_c >= 0)
      {
         return m_c;
      }
      else
      {
         return m_p->get_size();
      }

   }

   class class_size & operator ++()
   {

      m_p->set_size(m_p->get_size() + 1);

      return *this;

   }

   class class_size & operator --()
   {

      m_p->set_size(m_p->get_size() - 1);

      return *this;

   }


   class class_size operator ++(int)
   {

      class_size size(m_p, m_p->get_size());

      m_p->set_size(m_p->get_size() + 1);

      return size;

   }

   class class_size operator --(int)
   {

      class_size size(m_p, m_p->get_size());

      m_p->set_size(m_p->get_size() - 1);

      return size;

   }



   class class_size & operator +=(::count c)
   {

      m_p->set_size(m_p->get_size() + c);

      return *this;

   }

   class class_size & operator -=(::count c)
   {

      m_p->set_size(m_p->get_size() - c);

      return *this;

   }

};






#include "collection_pair.h"


#include "collection_array.h"
#include "collection_raw_array.h"
#include "collection_smart_pointer_array.h"
#include "collection_comparable_eq_array.h"
#include "collection_comparable_array.h"
#include "collection_comparable_raw_array.h"
#include "collection_comparable_primitive_array.h"

#include "base/ca/ca_byte_serializable.h"

#include "collection_primitive_array.h"
#include "collection_numeric_array.h"

#include "collection_logic_array.h"

#include "collection_list.h"
#include "collection_comparable_eq_list.h"
#include "collection_comparable_list.h"


#include "collection_typed_ptr_array.h"
#include "collection_typed_pointer_array.h"


#include "collection_map_association.h"


#include "collection_map.h"
#include "collection_attrib_map.h"
#include "collection_int_map.h"
#include "collection_string_map.h"
#include "collection_strid_map.h"
#include "collection_map_to_smart_pointer.h"
#include "collection_fifo_map.h"
#include "collection_sort_map.h"


#include "collection_sort_array.h"


/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//::ca::object
   // Arrays
   class byte_array;           // array of BYTE
   class uint16_array;           // array of WORD
   class uint32_array;          // array of uint32_t
   class CUIntArray;           // array of UINT
   class CPtrArray;            // array of void *
   class CObArray;             // array of ::ca::object*

   // Lists
   class pointer_list;             // list of void *
   class object_list;              // list of ::ca::object*

   // Maps (aka Dictionaries)
   class CMapWordToOb;         // map from WORD to ::ca::object*
   class CMapWordToPtr;        // map from WORD to void *
   class CMapPtrToWord;        // map from void * to WORD
   class map_ptr_to_ptr;         // map from void * to void *

   // Special string variants
   class string_list;          // list of Strings
   class CMapStringToPtr;      // map from string to void *
   class CMapStringToOb;       // map from string to ::ca::object*
   class string_to_string_map;   // map from string to string







#include "collection_pointer_list.h"
#include "collection_object_list.h"
#include "collection_typed_ptr_list.h"
#include "collection_typed_pointer_list.h"
#include "collection_string_list.h"


class CLASS_DECL_ca2 map_word_to_ptr :
   virtual public map < WORD, WORD, void *, void * >
{
public:
   map_word_to_ptr(::ca::application * papp = ::null(), ::count nBlockSize = 10);
};

class CLASS_DECL_ca2 map_ptr_to_word :
   virtual public map < void *, void *, WORD, WORD >
{
public:
   map_ptr_to_word(::ca::application * papp = ::null(), ::count nBlockSize = 10);
};


class CLASS_DECL_ca2 map_ptr_to_ptr :
   virtual public map < void *, void *, void *, void * >
{
public:
   map_ptr_to_ptr(::ca::application * papp = ::null(), ::count nBlockSize = 10);
};

class CLASS_DECL_ca2 map_word_to_ob :
   virtual public map < WORD, WORD, ::ca::object *, ::ca::object * >
{
public:
   map_word_to_ob(::ca::application * papp = ::null(), ::count nBlockSize = 10);
};


class CLASS_DECL_ca2 map_string_to_ptr :
   virtual public map < string, const string &, void *, void * >
{
public:
   map_string_to_ptr(::ca::application * papp = ::null(), ::count nBlockSize = 10);
};

class CLASS_DECL_ca2 map_string_to_ob :
   virtual public map < string, const string &, ::ca::object *, ::ca::object * >
{
public:
   map_string_to_ob(::ca::application * papp = ::null(), ::count nBlockSize = 10);
};





#include "collection_string_to_string_map.h"
#include "collection_bit_array.h"
#include "collection_string_array.h"

#include "base/ca/ca_variable_strict_compare.h"

#include "primitive/primitive_var.h"

#include "collection_stringa.h"


#include "base/ca/ca_var_array.h"
#include "base/ca/ca_property.h"




#include "base/ca/ca_signal.h"
#include "base/ca/ca_property_set.h"
#include "base/ca/ca_international2.h"


#include "collection_point_array.h"
#include "collection_rect_array.h"


#include "collection_string_to_string_map.h"


#include "collection_typed_pointer_map.h"

// inline
#include "collection.inl"


class CLASS_DECL_ca2 dword_2darray :
   public spa(uint32_array)
{
public:
};

class CLASS_DECL_ca2 index_2darray :
   public spa(index_array)
{
public:
};



#include "collection_sort.h"

#include "collection_id_array.h"

#include "collection_array.h"

#include "collection_bitset.h"

#include "collection_packset.h"

#include "collection_spreadset.h"

#include "collection_deque.h"

#include "collection_queue.h"

#include "collection_priority_queue.h"

class CLASS_DECL_ca2 time_array :
   public array < ::datetime::time, ::datetime::time & >
{
};


