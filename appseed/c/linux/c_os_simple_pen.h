#pragma once


class CLASS_DECL_c simple_pen
{
public:


   int                  m_iStock;
   int                  m_iStyle;
   int                  m_iWidth;
   COLORREF             m_cr;


   simple_pen();
   ~simple_pen();

   bool create_solid(int iWidth, COLORREF cr);
   bool from_stock(int iId);

   bool destroy();

   simple_pen & operator = (const simple_pen & pen);

};


