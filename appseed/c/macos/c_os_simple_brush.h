//
//  c_os_simple_brush.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//


class CLASS_DECL_c simple_brush
{
public:
   
   
   enum e_type
   {
      type_solid,
      type_stock,
   };
   
   
   e_type                  m_etype;
   COLORREF                m_cr;
   int                     m_iStock;
   
   
   
   simple_brush();
   ~simple_brush();
   
   
   
};
