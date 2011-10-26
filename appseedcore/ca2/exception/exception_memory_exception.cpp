#include "StdAfx.h"


memory_exception::memory_exception()
   : simple_exception() 
{

}

memory_exception::memory_exception(BOOL bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) 
{
   m_nResourceID = nResourceID; 
}

memory_exception::~memory_exception()
{

}
