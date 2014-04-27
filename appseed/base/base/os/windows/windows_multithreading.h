#pragma once


#ifdef cplusplus


class thread_data
{
public:


   static _declspec(thread) void *        t_p;


   void * get();
   void set(void * p);


};


#endif


