#pragma once

#include "raw_array.h"
#include "comparable_array.h"
#include "primitive/numeric_info.h"

template<class TYPE, class ARG_TYPE = const TYPE &>
class comparable_eq_raw_array :
   public comparable_eq_array < TYPE, ARG_TYPE, raw_array < TYPE, ARG_TYPE > >
{
};


template<class TYPE, class ARG_TYPE = const TYPE &>
class comparable_raw_array :
   public comparable_array < TYPE, ARG_TYPE, comparable_eq_raw_array < TYPE, ARG_TYPE > >
{
public:
};

