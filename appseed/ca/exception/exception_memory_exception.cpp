#include "framework.h"


memory_exception::memory_exception()
   : simple_exception() 
{

}

memory_exception::memory_exception(bool bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) 
{
   m_nResourceID = nResourceID; 
}

memory_exception::~memory_exception()
{

}
