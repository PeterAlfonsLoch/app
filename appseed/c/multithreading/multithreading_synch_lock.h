#pragma once


class CLASS_DECL_c synch_lock :
   public initial_single_lock
{
public:
   
   explicit synch_lock(waitable * pObject) : initial_single_lock(pObject) {}

};
