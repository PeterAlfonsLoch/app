#pragma once


class CLASS_DECL_c simple_brush
{
public:


   enum e_type
   {
     type_solid,
     type_linear_gradient,
     type_stock,

   };


   int                  m_iStyle;
   COLORREF             m_cr;
   int                  m_iStock;



   simple_brush();
   ~simple_brush();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(simple_graphics & g, COLORREF cr);
   bool create_linear_gradient(simple_graphics & g, POINT np1, POINT np2, COLORREF cr1, COLORREF cr2);
   bool destroy();


   // platform-specific
   bool from_stock(int iId);


};
