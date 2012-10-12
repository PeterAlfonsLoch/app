#include "framework.h"

simple_pen::simple_pen()
{
   
   m_hpen = NULL;

}

simple_pen::~simple_pen()
{
   
   if(m_hpen != NULL)
   {

      destroy();

   }

}

bool simple_pen::create_solid(int iWidth, COLORREF cr)
{

   m_hpen = ::CreatePen(PS_SOLID, iWidth, cr);

   if(m_hpen == NULL)
      return false;

   return TRUE;

}

bool simple_pen::destroy()
{
   
   if(m_hpen == NULL)
      return true;


   bool bOk = ::DeleteObject(m_hpen) != FALSE;

   m_hpen = NULL;

   if(!bOk)
      return false;

   return true;

}


