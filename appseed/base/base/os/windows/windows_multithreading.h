#pragma once


#ifdef cplusplus


class thread_data_base
{
public:


   static _declspec(thread) void *        t_p;


};


class CLASS_DECL_BASE thread_data :
   public thread_data_base
{
public:


   void * get();
   void set(void * p);


};


#endif


