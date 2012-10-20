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

bool simple_brush::create_solid(simple_graphics & g, COLORREF cr)
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

bool simple_brush::create_linear_gradient(simple_graphics & g, POINT np1, POINT np2, COLORREF cr1, COLORREF cr2)
{
   
   D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES prop;

   prop.startPoint.x    = (FLOAT) np1.x;
   prop.startPoint.y    = (FLOAT) np1.y;
   prop.endPoint.x      = (FLOAT) np2.x;
   prop.endPoint.y      = (FLOAT) np2.y;

   // Create an array of gradient stops to put in the gradient stop
   // collection that will be used in the gradient brush.
   ID2D1GradientStopCollection * pgradientstops = NULL;

   D2D1_GRADIENT_STOP gradientstops[2];

   gradientstops[0].color.a = GetAValue(cr1) / 255.0f;
   gradientstops[0].color.r = GetRValue(cr1) / 255.0f;
   gradientstops[0].color.g = GetGValue(cr1) / 255.0f;
   gradientstops[0].color.b = GetBValue(cr1) / 255.0f;
   gradientstops[0].position = 0.0f;
   gradientstops[1].color.a = GetAValue(cr2) / 255.0f;
   gradientstops[1].color.r = GetRValue(cr2) / 255.0f;
   gradientstops[1].color.g = GetGValue(cr2) / 255.0f;
   gradientstops[1].color.b = GetBValue(cr2) / 255.0f;
   gradientstops[1].position = 1.0f;

   // Create the ID2D1GradientStopCollection from a previously
   // declared array of D2D1_GRADIENT_STOP structs.
   HRESULT hr = g.m_pdc->CreateGradientStopCollection(gradientstops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pgradientstops);

   hr = g.m_pdc->CreateLinearGradientBrush(&prop, NULL, pgradientstops, &m_plineargradientbrush);

   pgradientstops->Release();

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



