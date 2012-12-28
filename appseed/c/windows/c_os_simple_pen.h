#pragma once


class CLASS_DECL_c simple_pen
{
public:

   
   Gdiplus::Pen *             m_ppen;
   bool                       m_bDelete;


   simple_pen();
   ~simple_pen();

   bool create_solid(simple_graphics & g, COLORREF cr, int32_t iWidth = 1);

   bool destroy();

   simple_pen & operator = (const simple_pen & pen);

};



