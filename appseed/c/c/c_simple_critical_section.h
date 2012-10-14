#pragma once


#ifdef WINDOWS


class CLASS_DECL_c simple_critical_section
{
public:


   CRITICAL_SECTION         m_criticalsection;


   simple_critical_section();
   ~simple_critical_section();


   inline void lock();
   inline void unlock();


};




#else


class CLASS_DECL_c simple_critical_section :
    public simple_mutex
{
public:


};


#endif


#ifdef WINDOWS


inline void simple_critical_section::lock()
{
   
   

   EnterCriticalSection(&m_criticalsection);

}


inline void simple_critical_section::unlock()
{
   
   LeaveCriticalSection(&m_criticalsection);

}


#endif


