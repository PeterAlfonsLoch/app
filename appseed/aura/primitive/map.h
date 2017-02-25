#pragma once


#include "collection/collection_common.h"
#include "collection/collection_pair.h"


#include "collection/collection_map_association.h"
#include "collection/collection_map.h"
#include "collection/collection_string_map.h"
#include "collection/collection_int_map.h"
#include "collection/collection_string_to_string_map.h"




using string_to_int_to_string = string_map < int_to_string >;

using string_to_string_to_int = string_map < string_to_int >;

namespace aura
{

   class CLASS_DECL_AURA session_map :
      virtual public ::map < index, index, ::aura::session *, ::aura::session * >
   {


   };

} // namespace aura


#include "collection/collection_map_impl.inl"


