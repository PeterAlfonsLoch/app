#include "StdAfx.h"

#ifdef _WINDOWS

simple_critical_section::simple_critical_section()
{
   InitializeCriticalSection(&m_criticalsection);
}


simple_critical_section::~simple_critical_section()
{
   DeleteCriticalSection(&m_criticalsection);
}

void simple_critical_section::lock()
{
   EnterCriticalSection(&m_criticalsection);
}

void simple_critical_section::unlock()
{
   LeaveCriticalSection(&m_criticalsection);
}

#endif // _WINDOWS