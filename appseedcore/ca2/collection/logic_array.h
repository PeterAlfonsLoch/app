#pragma once


#include "ex1/ex1_serializable.h"


class CLASS_DECL_ca bool_array :
   public ex1::serializable_array < raw_array < bool, bool > >
{
public:
};
