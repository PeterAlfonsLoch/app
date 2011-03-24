#include "StdAfx.h"


ptr::ptr()
{
   m_bUnkeep = true;
   if(m_pinterface != NULL)
   {
      m_pinterface->keep(this);
   }
}

ptr::~ptr()
{
   if(m_bUnkeep && m_pinterface != NULL)
   {
      m_pinterface->unkeep(this);
   }
}


