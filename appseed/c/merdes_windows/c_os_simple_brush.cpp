#include "framework.h"


simple_brush::simple_brush()
{

   m_etype        = type_none;
   m_pbrush       = NULL;
   m_psolidbrush  = NULL;

}

simple_brush::~simple_brush()
{
   
   if(m_pbrush != NULL || m_psolidbrush != NULL)
   {

      destroy();

   }

}

bool simple_brush::create_solid(COLORREF cr, simple_graphics & g)
{

   if(m_pbrush != NULL || m_psolidbrush != NULL)
   {

      destroy();

   }

   m_etype = type_solid;

   D2D1_COLOR_F c;

   c.a = GetAValue(cr) / 255.0f;
   c.r = GetRValue(cr) / 255.0f;
   c.g = GetGValue(cr) / 255.0f;
   c.b = GetBValue(cr) / 255.0f;

   g.m_pdc->CreateSolidColorBrush(c, &m_psolidbrush);

   if(m_psolidbrush == NULL)
   {
      
      m_etype = type_none;

      return false;

   }

   return true;

}


bool simple_brush::from_stock(int iId)
{

   if(m_pbrush != NULL || m_psolidbrush != NULL)
   {

      destroy();

   }

   if(iId == NULL_BRUSH)
   {
      m_etype = type_null;
   }
   else
   {
      return false;
   }

   return true;


}



bool simple_brush::destroy()
{

   if(m_pbrush == NULL && m_psolidbrush == NULL)
   {

      return true;

   }

   if(m_etype == type_solid)
   {
      
      m_psolidbrush->Release();

   }
   else if(m_etype == type_brush)
   {

      m_pbrush->Release();

   }

   
   m_pbrush = NULL;

   m_psolidbrush = NULL;

   return true;

}



ID2D1Brush * simple_brush::get_os_data()
{

   if(m_etype == type_solid)
   {

      return m_psolidbrush;

   }
   else if(m_etype == type_brush)
   {

      return m_pbrush;

   }

   return NULL;

}



