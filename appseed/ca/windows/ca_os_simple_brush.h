#pragma once


class CLASS_DECL_ca simple_brush
{
public:

   
   Gdiplus::Brush *           m_pbrush;
   bool                       m_bDelete;


   simple_brush();
   ~simple_brush();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(simple_graphics & g, COLORREF cr);
   bool create_linear_gradient(simple_graphics & g, POINT np1, POINT np2, COLORREF cr1, COLORREF cr2);
   bool destroy();


   // platform-specific
   bool from_stock(int32_t iId);


   simple_brush & operator = (const simple_brush & brush);


};


