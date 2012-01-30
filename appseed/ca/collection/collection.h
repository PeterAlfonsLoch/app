#pragma once


#include "template/template.h"


#include "raw_array.h"
#include "primitive_array.h"
#include "numeric_array.h"

#include "logic_array.h"

#include "list.h"
#include "comparable_eq_list.h"
#include "comparable_list.h"

#include "map.h"

#include "comparable_array.h"

#include "typed_ptr_array.h"
#include "typed_pointer_array.h"

#include "array_ptr.h"
#include "array_del_ptr.h"
#include "array_ptr_copy.h"
#include "array_ptr_alloc.h"

#include "array_release_ptr.h"
#include "array_smart_ptr.h"

#include "array_parent_alloc.h"

#include "array_app_alloc.h"

#include "sort_array.h"
#include "class_sort_array.h"




/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//::radix::object
   // Arrays
   class byte_array;           // base_array of BYTE
   class word_array;           // base_array of WORD
   class dword_array;          // base_array of DWORD
   class CUIntArray;           // base_array of UINT
   class CPtrArray;            // base_array of void *
   class CObArray;             // base_array of ::radix::object*

   // Lists
   class pointer_list;             // list of void *
   class object_list;              // list of ::radix::object*

   // Maps (aka Dictionaries)
   class CMapWordToOb;         // ::collection::map from WORD to ::radix::object*
   class CMapWordToPtr;        // ::collection::map from WORD to void *
   class CMapPtrToWord;        // ::collection::map from void * to WORD
   class map_ptr_to_ptr;         // ::collection::map from void * to void *

   // Special string variants
   class string_list;          // list of Strings
   class CMapStringToPtr;      // ::collection::map from string to void *
   class CMapStringToOb;       // ::collection::map from string to ::radix::object*
   class string_to_string_map;   // ::collection::map from string to string







#include "pointer_list.h"
#include "object_list.h"
#include "typed_ptr_list.h"
#include "typed_pointer_list.h"
#include "string_list.h"


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
   virtual public ::collection::map < WORD, WORD, ::radix::object *, ::radix::object * >
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
   virtual public ::collection::map < string, const string &, ::radix::object *, ::radix::object * >
{
public:
   map_string_to_ob(::count nBlockSize = 10);
};





#include "string_to_string_map.h"
#include "bit_array.h"
#include "collection/string_array.h"
#include "gen/gen_var_array.h"
#include "gen/gen_property.h"
#include "gen/gen_international2.h"
#include "point_array.h"
#include "rect_array.h"


#include "string_to_string_map.h"

#include "typed_pointer_map.h"

// inline
#include "collection.inl"


class CLASS_DECL_ca dword_2darray :
   public array_ptr_alloc < dword_array, dword_array & >
{
public:
};

class CLASS_DECL_ca index_2darray :
   public array_ptr_alloc < index_array, index_array & >
{
public:
};



#include "sort.h"

#include "id_array.h"

#include "array.h"

#include "bitset.h"



