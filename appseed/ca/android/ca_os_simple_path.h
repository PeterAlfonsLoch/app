#pragma once


class CLASS_DECL_c os_simple_path
{
public:


   class CLASS_DECL_c arc
   {
   public:


      double   m_xCenter;
      double   m_yCenter;
      double   m_dRadiusX;
      double   m_dRadiusY;
      double   m_dAngle1;
      double   m_dAngle2;


   };


   class CLASS_DECL_c line
   {
   public:

      double   m_x1;
      double   m_y1;
      double   m_x2;
      double   m_y2;


   };


   class CLASS_DECL_c element
   {
   public:


         enum e_type
         {
            type_begin,
            type_arc,
            type_line,
            type_close,
         };


         union
         {


            arc      m_arc;
            line     m_line;

         };

         e_type m_etype;


   };

   simple_array < element >      m_elementa;
   bool                          m_bFill;
   ::ca2::e_fill_mode            m_efillmode;


   os_simple_path();
   ~os_simple_path();


   bool begin_figure(bool bFill, ::ca2::e_fill_mode efillmode);
   bool end_figure(bool bClose);


   bool add_arc(const RECT & rect, int32_t iStart, int32_t iAngle);
   bool add_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);




};






