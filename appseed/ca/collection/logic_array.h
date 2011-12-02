#pragma once


#include "ca/ex1/ex1_byte_serializable.h"
#include "ca/collection/raw_array.h"


class CLASS_DECL_ca bool_array :
   virtual public ex1::byte_serializable_array < raw_array < bool, bool > >
{
public:
};
