#pragma once


class CLASS_DECL_ca simple_brush
{
public:

   enum e_type
   {
      type_none,
      type_brush,
      type_solid,
      type_linear_gradient,
      type_null,
   };


   e_type                        m_etype;

   union
   {
      
      ID2D1Brush *                  m_pbrush;

      ID2D1SolidColorBrush *        m_psolidbrush;

      ID2D1LinearGradientBrush *    m_plineargradientbrush;

   };



   simple_brush();
   ~simple_brush();


   virtual bool create_solid(simple_graphics & g, COLORREF cr);
   virtual bool create_linear_gradient(simple_graphics & g, POINT np1, POINT np2, COLORREF cr1, COLORREF cr2);
   virtual bool from_stock(int iId);

   virtual bool destroy();


   ID2D1Brush * get_os_data();

   simple_brush & operator = (const simple_brush & brush);

};




