#pragma once


class CLASS_DECL_c simple_pen
{
public:


   enum e_type
   {
      type_solid,
      type_stock,
   };


   int                  m_iStock;
   e_type               m_etype;
   int                  m_iWidth;
   COLORREF             m_cr;


   simple_pen();
   ~simple_pen();

   bool create_solid(simple_graphics & g, COLORREF cr, int iWidth = 1);
   bool from_stock(int iId);

   bool destroy();

   simple_pen & operator = (const simple_pen & pen);

};


