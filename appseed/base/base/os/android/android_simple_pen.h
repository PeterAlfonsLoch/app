#pragma once


class CLASS_DECL_BASE simple_pen
{
public:


   enum e_type
   {
      type_solid,
      type_stock,
   };


   int32_t                  m_iStock;
   e_type               m_etype;
   int32_t                  m_iWidth;
   COLORREF             m_cr;


   simple_pen();
   ~simple_pen();

   bool create_solid(::draw2d::graphics * pgraphics, COLORREF cr, int32_t iWidth = 1);
   bool from_stock(int32_t iId);

   bool destroy();

   simple_pen & operator = (const simple_pen & pen);

};


