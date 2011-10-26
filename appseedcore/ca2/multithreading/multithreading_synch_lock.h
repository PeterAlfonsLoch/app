#pragma once


class CLASS_DECL_ca synch_lock :
   public single_lock
{
public:


   synch_lock(sync_object_base * pObject);
   ~synch_lock();


};
