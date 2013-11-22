//
//  c_os_simple_pen.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//

#pragma once


class CLASS_DECL_BOOT simple_pen
{
public:
   
   
   enum e_type
   {
      type_null,
      type_solid,
   };
   
   enum e_end_cap
   {
      end_cap_flat,
      end_cap_round,
   };
   
   
   enum e_line_join
   {
      line_join_miter,
      line_join_bevel,
      line_join_round,
      line_join_miter_clipped,
   };
   
   e_type            m_etype;
   e_end_cap         m_eendcap;
   e_line_join       m_elinejoin;
   double            m_dWidth;
   COLORREF          m_cr;
   

   simple_pen();
   ~simple_pen();
   
   
   bool create_solid(simple_graphics & g, COLORREF cr, int iWidth = 1);
   bool from_stock(int iId);
   
   bool destroy();
   
   simple_pen & operator = (const simple_pen & pen);
   
};


