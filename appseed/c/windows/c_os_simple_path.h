#pragma once





class CLASS_DECL_c simple_path
{
public:

   
   Gdiplus::GraphicsPath *       m_ppath;
   bool                          m_bFill;
   

   simple_path(bool bFill);
   ~simple_path();


   bool add_arc(const RECT & rect, int iStart, int iAngle);
   bool add_line(int x1, int y1, int x2, int y2);


   bool close_figure();

};






