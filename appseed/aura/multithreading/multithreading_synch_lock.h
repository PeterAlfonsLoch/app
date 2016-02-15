#pragma once


class CLASS_DECL_AURA synch_lock :
   public initial_single_lock
{
public:


   explicit synch_lock(sync_object * pobject) :
      initial_single_lock(pobject)
   {


   }


};





