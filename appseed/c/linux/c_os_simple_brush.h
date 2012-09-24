#pragma once


class CLASS_DECL_c simple_brush
{
public:


   int                  m_iStyle;
   COLORREF             m_cr;
   int                  m_iStock;


   simple_brush();
   ~simple_brush();


   // aim to be all-platoform - but if there is no equivalent because no op : create empty method
   bool create_solid(COLORREF cr);
   bool destroy();


   // platform-specific
   bool from_stock(int iId);


};
