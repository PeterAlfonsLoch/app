#pragma once




template<class TYPE, class ARG_TYPE = const TYPE &>
class comparable_eq_raw_array :
   public comparable_eq_array < TYPE, ARG_TYPE, array < TYPE, ARG_TYPE > >
{
};


template<class TYPE, class ARG_TYPE = const TYPE &>
class comparable_raw_array :
   public comparable_array < TYPE, ARG_TYPE, comparable_eq_raw_array < TYPE, ARG_TYPE > >
{
public:
};

