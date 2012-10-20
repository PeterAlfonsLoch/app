#include "framework.h"
#undef new
#include <gdiplus.h>


simple_pen::simple_pen()
{
   
   m_ppen      = NULL;

   m_bDelete   = false;

}


simple_pen::~simple_pen()
{
   
   if(m_ppen != NULL)
   {

      destroy();

   }

}


bool simple_pen::create_solid(simple_graphics & g, COLORREF cr, int iWidth)
{

   UNREFERENCED_PARAMETER(g);

   if(m_ppen != NULL)
   {

      destroy();

   }

   m_ppen = new Gdiplus::Pen(Gdiplus::Color(GetAValue(cr), GetRValue(cr), GetGValue(cr), GetBValue(cr)), iWidth);

   if(m_ppen == NULL)
      return false;

   m_bDelete = true;

   return TRUE;

}

bool simple_pen::destroy()
{
 
   if(m_ppen == NULL)
      return true;

   bool bOk = true;

   if(m_bDelete)
   {

      try
      {

         delete m_ppen;

      }
      catch(...)
      {

         bOk = false;

      }

   }

   m_bDelete = false;
   
   m_ppen = NULL;

   if(!bOk)
      return false;

   return true;

}



simple_pen & simple_pen::operator = (const simple_pen & pen)
{

   if(m_ppen != NULL)
   {

      destroy();

   }

   m_bDelete = false;

   m_ppen = pen.m_ppen;

   return *this;

}









