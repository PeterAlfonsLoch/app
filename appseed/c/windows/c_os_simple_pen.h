#pragma once


class CLASS_DECL_c simple_pen
{
public:

   
   Gdiplus::Pen *       m_ppen;


   simple_pen();
   ~simple_pen();

   bool create_solid(int iWidth, COLORREF cr);

   bool destroy();



};



class CLASS_DECL_c simple_solid_pen :
   public simple_pen
{
public:


   simple_solid_pen(int iWidth, COLORREF cr)
   {

      create_solid(iWidth, cr);

   }

};