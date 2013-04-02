#pragma once


#include "collection_base_array.h"
#include "collection_smart_pointer_array.h"


#include "collection_raw_array.h"
#include "collection_comparable_eq_array.h"
#include "collection_comparable_array.h"
#include "collection_comparable_raw_array.h"
#include "collection_comparable_primitive_array.h"

#include "ca/ca/ca_byte_serializable.h"

#include "collection_primitive_array.h"
#include "collection_numeric_array.h"

#include "collection_logic_array.h"

#include "collection_list.h"
#include "collection_comparable_eq_list.h"
#include "collection_comparable_list.h"


#include "collection_typed_ptr_array.h"
#include "collection_typed_pointer_array.h"


#include "collection_sort_array.h"
#include "collection_class_sort_array.h"


#include "collection_map.h"
#include "collection_map_to_smart_pointer.h"
#include "collection_fifo_map.h"
#include "collection_sort_map.h"


/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//::ca::object
   // Arrays
   class byte_array;           // base_array of BYTE
   class uint16_array;           // base_array of WORD
   class uint32_array;          // base_array of uint32_t
   class CUIntArray;           // base_array of UINT
   class CPtrArray;            // base_array of void *
   class CObArray;             // base_array of ::ca::object*

   // Lists
   class pointer_list;             // list of void *
   class object_list;              // list of ::ca::object*

   // Maps (aka Dictionaries)
   class CMapWordToOb;         // ::collection::map from WORD to ::ca::object*
   class CMapWordToPtr;        // ::collection::map from WORD to void *
   class CMapPtrToWord;        // ::collection::map from void * to WORD
   class map_ptr_to_ptr;         // ::collection::map from void * to void *

   // Special string variants
   class string_list;          // list of Strings
   class CMapStringToPtr;      // ::collection::map from string to void *
   class CMapStringToOb;       // ::collection::map from string to ::ca::object*
   class string_to_string_map;   // ::collection::map from string to string







#include "collection_pointer_list.h"
#include "collection_object_list.h"
#include "collection_typed_ptr_list.h"
#include "collection_typed_pointer_list.h"
#include "collection_string_list.h"


class CLASS_DECL_ca map_word_to_ptr :
   virtual public ::collection::map < WORD, WORD, void *, void * >
{
public:
   map_word_to_ptr(::count nBlockSize = 10);
};

class CLASS_DECL_ca map_ptr_to_word :
   virtual public ::collection::map < void *, void *, WORD, WORD >
{
public:
   map_ptr_to_word(::count nBlockSize = 10);
};


class CLASS_DECL_ca map_ptr_to_ptr :
   virtual public ::collection::map < void *, void *, void *, void * >
{
public:
   map_ptr_to_ptr(::count nBlockSize = 10);
};

class CLASS_DECL_ca map_word_to_ob :
   virtual public ::collection::map < WORD, WORD, ::ca::object *, ::ca::object * >
{
public:
   map_word_to_ob(::count nBlockSize = 10);
};


class CLASS_DECL_ca map_string_to_ptr :
   virtual public ::collection::map < string, const string &, void *, void * >
{
public:
   map_string_to_ptr(::count nBlockSize = 10);
};

class CLASS_DECL_ca map_string_to_ob :
   virtual public ::collection::map < string, const string &, ::ca::object *, ::ca::object * >
{
public:
   map_string_to_ob(::count nBlockSize = 10);
};





#include "collection_string_to_string_map.h"
#include "collection_bit_array.h"
#include "collection_string_array.h"

#include "ca/ca/ca_variable_strict_compare.h"

#include "ca/primitive/primitive_var.h"

#include "collection_stringa.h"


#include "ca/ca/ca_var_array.h"
#include "ca/ca/ca_property.h"




#include "ca/ca/ca_signal.h"
#include "ca/ca/ca_property_set.h"
#include "ca/ca/ca_international2.h"


#include "collection_point_array.h"
#include "collection_rect_array.h"


#include "collection_string_to_string_map.h"


#include "collection_typed_pointer_map.h"

// inline
#include "collection.inl"


class CLASS_DECL_ca dword_2darray :
   public spa(uint32_array)
{
public:
};

class CLASS_DECL_ca index_2darray :
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

class CLASS_DECL_ca time_array :
   public base_array < ::datetime::time, ::datetime::time & >
{
};


