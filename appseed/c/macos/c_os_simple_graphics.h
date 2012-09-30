//
//  c_os_simple_graphics.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//



class CLASS_DECL_c simple_graphics
{
public:
   
#ifdef __cplusplus
   void *                  m_pnsgc;
#else
   NSGraphicsContext *     m_nsgc;
#endif
   
   simple_graphics();
   ~simple_graphics();
   
   
};
