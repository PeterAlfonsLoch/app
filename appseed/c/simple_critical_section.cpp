#include "framework.h"


#ifdef WINDOWS


simple_critical_section::simple_critical_section()
{
   InitializeCriticalSection(&m_criticalsection);
}


simple_critical_section::~simple_critical_section()
{
   DeleteCriticalSection(&m_criticalsection);
}


#endif // WINDOWS



