#include "framework.h"


#ifdef WINDOWS


simple_critical_section::simple_critical_section()
{
   InitializeCriticalSectionEx(&m_criticalsection, 4000, 0);
}


simple_critical_section::~simple_critical_section()
{
   DeleteCriticalSection(&m_criticalsection);
}


#endif // WINDOWS



