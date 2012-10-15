#pragma once





class CLASS_DECL_c simple_path
{
public:

   
   Gdiplus::GraphicsPath *       m_ppath;
   

   simple_path();
   ~simple_path();


   bool add_arc(const RECT & rect, int iStart, int iAngle);

};






