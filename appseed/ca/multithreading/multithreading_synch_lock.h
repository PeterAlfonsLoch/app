#pragma once


class CLASS_DECL_ca synch_lock :
   public single_lock
{
public:


   synch_lock(waitable * pObject);
   ~synch_lock();


};
