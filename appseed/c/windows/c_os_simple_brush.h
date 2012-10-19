#pragma once


class CLASS_DECL_c simple_brush
{
public:

   
   Gdiplus::Brush *        m_pbrush;


   simple_brush();
   ~simple_brush();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(COLORREF cr, simple_graphics & g);
   bool create_liner_gradient(POINT np1, POINT np2, COLORREF cr1, COLORREF cr2);
   bool destroy();


   // platform-specific
   bool from_stock(int iId);


};


