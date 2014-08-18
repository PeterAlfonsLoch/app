#pragma once





//#include "collection_iterator.h"

#include "collection_pair.h"



#include "collection_list.h"
#include "collection_comparable_eq_list.h"
#include "collection_comparable_list.h"


#include "collection_typed_ptr_array.h"



#include "collection_map_association.h"


#include "collection_map.h"
#include "collection_attrib_map.h"
#include "collection_int_map.h"
#include "collection_string_map.h"
#include "collection_strid_map.h"
#include "collection_map_to_smart_pointer.h"


class pointer_list;             // list of void *
class object_list;              // list of object*

class map_ptr_to_ptr;         // map from void * to void *

class string_list;          // list of Strings
class string_to_string;   // map from string to string







#include "collection_pointer_list.h"
#include "collection_object_list.h"
#include "collection_typed_ptr_list.h"
#include "collection_typed_pointer_list.h"
#include "collection_string_list.h"


class CLASS_DECL_AXIS map_word_to_ptr :
   virtual public map < WORD, WORD, void *, void * >
{
public:
   map_word_to_ptr(sp(::axis::application) papp = NULL, ::count nBlockSize = 10);
};

class CLASS_DECL_AXIS map_ptr_to_word :
   virtual public map < void *, void *, WORD, WORD >
{
public:
   map_ptr_to_word(sp(::axis::application) papp = NULL, ::count nBlockSize = 10);
};


class CLASS_DECL_AXIS map_ptr_to_ptr :
   virtual public map < void *, void *, void *, void * >
{
public:
   map_ptr_to_ptr(sp(::axis::application) papp = NULL, ::count nBlockSize = 10);
};

class CLASS_DECL_AXIS map_word_to_ob :
   virtual public map < WORD, WORD, object *, object * >
{
public:
   map_word_to_ob(sp(::axis::application) papp = NULL, ::count nBlockSize = 10);
};


class CLASS_DECL_AXIS map_string_to_ptr :
   virtual public map < string, const string &, void *, void * >
{
public:
   map_string_to_ptr(sp(::axis::application) papp = NULL, ::count nBlockSize = 10);
};

class CLASS_DECL_AXIS map_string_to_ob :
   virtual public map < string, const string &, object *, object * >
{
public:
   map_string_to_ob(sp(::axis::application) papp = NULL, ::count nBlockSize = 10);
};





#include "collection_string_array.h"





#include "collection_typed_pointer_map.h"








#include "collection_bitset.h"

#include "collection_packset.h"

#include "collection_deque.h"

#include "collection_queue.h"

#include "collection_priority_queue.h"

#include "collection_lemon_array.h"

#include "collection_stack.h"


