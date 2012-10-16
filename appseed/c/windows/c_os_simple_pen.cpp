#include "framework.h"
#undef new
#include <gdiplus.h>

simple_pen::simple_pen()
{
   
   m_ppen = NULL;

}

simple_pen::~simple_pen()
{
   
   if(m_ppen != NULL)
   {

      destroy();

   }

}

bool simple_pen::create_solid(COLORREF cr, int iWidth)
{

   if(m_ppen != NULL)
   {

      destroy();

   }

   m_ppen = new Gdiplus::Pen(Gdiplus::Color(GetAValue(cr), GetRValue(cr), GetGValue(cr), GetBValue(cr)), iWidth);

   if(m_ppen == NULL)
      return false;

   return TRUE;

}

bool simple_pen::destroy()
{
 
   if(m_ppen == NULL)
      return true;

   bool bOk = true;

   try
   {

      delete m_ppen;

   }
   catch(...)
   {

      bOk = false;

   }
   
   m_ppen = NULL;

   if(!bOk)
      return false;

   return true;

}


