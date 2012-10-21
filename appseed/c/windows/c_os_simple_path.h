#pragma once





class CLASS_DECL_c os_simple_path
{
public:

   
   Gdiplus::GraphicsPath *       m_ppath;
   bool                          m_bFill;
   ::ca::e_fill_mode             m_efillmode;
   

   os_simple_path();
   ~os_simple_path();


   bool begin_figure(bool bFill, ::ca::e_fill_mode efillmode);
   bool end_figure(bool bClose);


   bool add_arc(const RECT & rect, int iStart, int iAngle);
   bool add_line(int x1, int y1, int x2, int y2);


   

};






