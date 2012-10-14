#pragma once


class CLASS_DECL_c simple_brush
{
public:

   
   Gdiplus::Brush *        m_pbrush;


   simple_brush();
   ~simple_brush();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(COLORREF cr);
   bool create_liner_gradient(POINT np1, POINT np2, COLORREF cr1, COLORREF cr2);
   bool destroy();


   // platform-specific
   bool from_stock(int iId);


};



class CLASS_DECL_c simple_solid_brush :
   public simple_brush
{
public:

   simple_solid_brush(COLORREF cr)
   {
      create_solid(cr);
   }

};