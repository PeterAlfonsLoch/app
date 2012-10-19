#pragma once


class CLASS_DECL_c simple_pen
{
public:

   
   Gdiplus::Pen *       m_ppen;


   simple_pen();
   ~simple_pen();

   bool create_solid(COLORREF cr, int iWidth);

   bool destroy();



};



