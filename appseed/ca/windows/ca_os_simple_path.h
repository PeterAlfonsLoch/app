#pragma once





class CLASS_DECL_ca os_simple_path
{
public:

   
   Gdiplus::GraphicsPath *       m_ppath;
   bool                          m_bFill;
   ::draw2d::e_fill_mode         m_efillmode;
   

   os_simple_path();
   ~os_simple_path();


   bool begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
   bool end_figure(bool bClose);


   bool add_arc(const RECT & rect, int32_t iStart, int32_t iAngle);
   bool add_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);


   

};






