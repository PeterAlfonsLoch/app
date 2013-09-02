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
   element(a.) \
   { \
    \
   m_nGrowBy      = a.m_nGrowBy; \
   m_pData        = a.m_pData; \
   m_nSize        = a.m_nSize; \
   m_nMaxSize     = a.m_nMaxSize; \
   \
   a.m_pData      = NULL; \
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
         a.m_pData      = NULL(); \
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

   class_size(C * p, ::count ca) : m_p(NULL), m_c(ca) {}

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



   class class_size & operator +=(::count ca)
   {

      m_p->set_size(m_p->get_size() + ca);

      return *this;

   }

   class class_size & operator -=(::count ca)
   {

      m_p->set_size(m_p->get_size() - ca);

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

#include "base/ca2/ca2_byte_serializable.h"

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

//object
   // Arrays
   class byte_array;           // array of BYTE
   class uint16_array;           // array of WORD
   class uint32_array;          // array of uint32_t
   class CUIntArray;           // array of UINT
   class CPtrArray;            // array of void *
   class CObArray;             // array of object*

   // Lists
   class pointer_list;             // list of void *
   class object_list;              // list of object*

   // Maps (aka Dictionaries)
   class CMapWordToOb;         // map from WORD to object*
   class CMapWordToPtr;        // map from WORD to void *
   class CMapPtrToWord;        // map from void * to WORD
   class map_ptr_to_ptr;         // map from void * to void *

   // Special string variants
   class string_list;          // list of Strings
   class CMapStringToPtr;      // map from string to void *
   class CMapStringToOb;       // map from string to object*
   class string_to_string_map;   // map from string to string







#include "collection_pointer_list.h"
#include "collection_object_list.h"
#include "collection_typed_ptr_list.h"
#include "collection_typed_pointer_list.h"
#include "collection_string_list.h"


class CLASS_DECL_c map_word_to_ptr :
   virtual public map < WORD, WORD, void *, void * >
{
public:
   map_word_to_ptr(sp(::application) papp = NULL, ::count nBlockSize = 10);
};

class CLASS_DECL_c map_ptr_to_word :
   virtual public map < void *, void *, WORD, WORD >
{
public:
   map_ptr_to_word(sp(::application) papp = NULL, ::count nBlockSize = 10);
};


class CLASS_DECL_c map_ptr_to_ptr :
   virtual public map < void *, void *, void *, void * >
{
public:
   map_ptr_to_ptr(sp(::application) papp = NULL, ::count nBlockSize = 10);
};

class CLASS_DECL_c map_word_to_ob :
   virtual public map < WORD, WORD, object *, object * >
{
public:
   map_word_to_ob(sp(::application) papp = NULL, ::count nBlockSize = 10);
};


class CLASS_DECL_c map_string_to_ptr :
   virtual public map < string, const string &, void *, void * >
{
public:
   map_string_to_ptr(sp(::application) papp = NULL, ::count nBlockSize = 10);
};

class CLASS_DECL_c map_string_to_ob :
   virtual public map < string, const string &, object *, object * >
{
public:
   map_string_to_ob(sp(::application) papp = NULL, ::count nBlockSize = 10);
};





#include "collection_string_to_string_map.h"
#include "collection_bit_array.h"
#include "collection_string_array.h"

#include "c/datetime/datetime_time.h"

#include "primitive/primitive_var.h"

#include "collection_stringa.h"


#include "collection_var_array.h"
#include "c/primitive/primitive_property.h"




#include "c/primitive/primitive_signal.h"
#include "c/primitive/primitive_property_set.h"


#include "collection_point_array.h"
#include "collection_rect_array.h"


#include "collection_string_to_string_map.h"


#include "collection_typed_pointer_map.h"

// inline
#include "collection.inl"


class CLASS_DECL_c dword_2darray :
   public spa(uint32_array)
{
public:
};

class CLASS_DECL_c index_2darray :
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

class CLASS_DECL_c time_array :
   public array < ::datetime::time, ::datetime::time & >
{
};


#include "collection_buffer.h"

#include "collection_stringl.h"
#include "collection_string_sort_array.h"
#include "collection_stringa.h"

#include "collection_numeric_array.h"

#include "collection_lemon_array.h"




