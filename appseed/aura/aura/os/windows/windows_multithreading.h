#pragma once


#ifdef cplusplus




class CLASS_DECL_AURA thread_data
{
public:

   
   DWORD g_dwTlsIndex;

   thread_data();
   ~thread_data();

   inline void * get();
   inline void set(void * p);


};

#ifdef WINDOWS

inline void * thread_data::get()
{

   return TlsGetValue(g_dwTlsIndex);

}


inline void thread_data::set(void * p)
{

   TlsSetValue(g_dwTlsIndex,(LPVOID)p);

}


#endif



#endif




CLASS_DECL_AURA int32_t get_os_thread_priority(int32_t iCa2Priority);


CLASS_DECL_AURA int32_t get_os_priority_class(int32_t iCa2Priority);


CLASS_DECL_AURA int32_t get_os_thread_scheduling_priority(int32_t iCa2Priority);


CLASS_DECL_AURA int32_t get_os_class_scheduling_priority(int32_t iCa2Priority);


