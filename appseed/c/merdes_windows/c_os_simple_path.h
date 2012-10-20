#pragma once





class CLASS_DECL_c simple_path
{
public:

   
   ID2D1PathGeometry *        m_ppath;
   ID2D1GeometrySink *        m_psink;
   bool                       m_bFill;
   

   simple_path(bool bFill);
   ~simple_path();


   bool add_arc(const RECT & rect, int iStart, int iAngle);

   bool add_line(int x1, int y1, int x2, int y2);
   inline bool add_line(POINT p1, POINT p2);

   bool add_rect(const RECT & rect);

   bool get_arc(D2D1_POINT_2F & pt, D2D1_ARC_SEGMENT & arcseg, const RECT & rect, int iStart, int iAngle);

   ID2D1PathGeometry * get_os_data();
   bool close_figure();


};







inline bool simple_path::add_line(POINT p1, POINT p2)
{
   return add_line(p1.x, p1.y, p2.x, p2.y);
}





