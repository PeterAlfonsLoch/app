#pragma once


#ifdef cplusplus




class CLASS_DECL_AXIS thread_data
{
public:

   
   DWORD g_dwTlsIndex;

   thread_data();
   ~thread_data();

   void * get();
   void set(void * p);


};


#endif




CLASS_DECL_AXIS int32_t get_os_thread_priority(int32_t iCa2Priority);


CLASS_DECL_AXIS int32_t get_os_priority_class(int32_t iCa2Priority);


CLASS_DECL_AXIS int32_t get_os_thread_scheduling_priority(int32_t iCa2Priority);


CLASS_DECL_AXIS int32_t get_os_class_scheduling_priority(int32_t iCa2Priority);



