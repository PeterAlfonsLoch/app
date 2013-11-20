#pragma once


class CLASS_DECL_BASE simple_brush
{
public:


   enum e_type
   {
     type_solid,
     type_linear_gradient,
     type_stock,

   };


   e_type               m_etype;
   COLORREF             m_cr;
   int32_t                  m_iStock;
   POINT                m_p1;
   POINT                m_p2;
   COLORREF             m_cr1;
   COLORREF             m_cr2;




   simple_brush();
   ~simple_brush();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(::draw2d::graphics * pgraphics, COLORREF cr);
   bool create_linear_gradient(::draw2d::graphics * pgraphics, POINT np1, POINT np2, COLORREF cr1, COLORREF cr2);
   bool destroy();


   // platform-specific
   bool from_stock(int32_t iId);


};
