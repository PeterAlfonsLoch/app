#pragma once




template < class TYPE, class ARG_TYPE = const TYPE & >
class comparable_eq_raw_array
{
public:


   typedef comparable_eq_array < TYPE, ARG_TYPE, raw_array < TYPE, ARG_TYPE > > type;


};


template < class TYPE, class ARG_TYPE = const TYPE & >
class comparable_raw_array
{
public:


   typedef comparable_array < TYPE, ARG_TYPE, typename comparable_eq_raw_array < TYPE, ARG_TYPE >::type > type;


};

