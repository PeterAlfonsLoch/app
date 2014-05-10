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




CLASS_DECL_BASE int32_t get_os_thread_priority(int32_t iCa2Priority);


CLASS_DECL_BASE int32_t get_os_priority_class(int32_t iCa2Priority);


CLASS_DECL_BASE int32_t get_os_thread_scheduling_priority(int32_t iCa2Priority);


CLASS_DECL_BASE int32_t get_os_class_scheduling_priority(int32_t iCa2Priority);



