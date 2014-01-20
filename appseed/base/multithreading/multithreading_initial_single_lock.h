#pragma once


class CLASS_DECL_BASE initial_single_lock :
   public single_lock
{
public:


   explicit initial_single_lock(waitable * pObject) :
      single_lock(pObject, true)
   { 
   
   }


};
