#pragma once


#ifdef _WINDOWS
class CLASS_DECL_____ simple_critical_section
{
public:


   CRITICAL_SECTION         m_criticalsection;


   simple_critical_section();
   ~simple_critical_section();


   void lock();
   void unlock();


};
#else

class CLASS_DECL_____ simple_critical_section :
    public simple_mutex
{
public:


};

#endif


