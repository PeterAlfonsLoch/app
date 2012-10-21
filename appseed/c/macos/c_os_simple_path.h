#pragma once





class CLASS_DECL_c os_simple_path
{
public:

   
//   ID2D1PathGeometry *        m_ppath;
  // ID2D1GeometrySink *        m_psink;
   bool                       m_bFill;
   

   os_simple_path();
   ~os_simple_path();

   bool begin_figure(bool bFill);
   bool end_figure(bool bClose);

   bool add_arc(const RECT & rect, int iStart, int iAngle);

   bool add_line(int x1, int y1, int x2, int y2);

   bool add_rect(const RECT & rect);

   //bool get_arc(D2D1_POINT_2F & pt, D2D1_ARC_SEGMENT & arcseg, const RECT & rect, int iStart, int iAngle);

   //ID2D1PathGeometry * get_os_data();


};












