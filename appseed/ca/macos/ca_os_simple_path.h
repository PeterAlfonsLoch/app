#pragma once


class CLASS_DECL_ca os_simple_path
{
public:

   
#ifdef __MM

   NSBezierPath *          m_nspath;
   
#else
   
   void *                  m_ppath;
   
#endif
   
   
   bool                       m_bFill;
   ::draw2d::e_fill_mode          m_efillmode;
   

   os_simple_path();
   ~os_simple_path();


   bool begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
   
   bool end_figure(bool bClose);

   bool add_arc(const RECT & rect, int iStart, int iAngle);

   bool add_line(int x1, int y1, int x2, int y2);

   bool add_line(int x, int y);
   
   bool add_rect(const RECT & rect);

   //bool get_arc(D2D1_POINT_2F & pt, D2D1_ARC_SEGMENT & arcseg, const RECT & rect, int iStart, int iAngle);

   //ID2D1PathGeometry * get_os_data();


};














