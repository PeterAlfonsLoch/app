#pragma once


namespace ca
{


   class CLASS_DECL_ca graphics_path :
      virtual public graphics_object
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

      class CLASS_DECL_c move
      {
      public:

         double   m_x;
         double   m_y;

      };


      class CLASS_DECL_c line
      {
      public:

         double   m_x;
         double   m_y;

      };

      class CLASS_DECL_c end
      {
      public:

         bool     m_bClose;

      };


      class CLASS_DECL_c element
      {
      public:


            enum e_type
            {
               type_begin,
               type_arc,
               type_line,
               type_move,
               type_end,
            };


            union
            {


               arc      m_arc;
               move     m_move;
               line     m_line;
               end      m_end;

            };

            e_type m_etype;


      };

      simple_array < element >      m_elementa;
      bool                          m_bFill;
      ::ca::e_fill_mode             m_efillmode;
      bool                          m_bHasPoint;
      point                         m_pt;
      bool                          m_bUpdated;


      graphics_path();
      virtual ~graphics_path();


      virtual bool has_current_point();
      virtual point last_point();



      virtual bool begin_figure(bool bFill, ::ca::e_fill_mode efillmode);
      virtual bool end_figure(bool bClose);


      //virtual bool is_empty();
      //virtual bool has_current_point();
      //virtual point current_point();

      virtual bool add_arc(const RECT & rect, int32_t iStart, int32_t iAngle);

      virtual bool add_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool add_line(point p1, point p2);

      virtual bool add_lines(const POINT * lppoint, int32_t nCount);

      virtual bool add_line(int32_t x, int32_t y);
      virtual bool add_line(point p);

      virtual bool add_move(int32_t x, int32_t y);
      virtual bool add_move(point p);

      virtual bool add_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool add_rect(LPCRECT lpcrect);

      virtual void * detach();

      virtual bool defer_update();
      virtual bool update();

   };


   class CLASS_DECL_ca graphics_path_sp :
      public smart_pointer < graphics_path >
   {
   public:

      graphics_path_sp()
      {
      }

      graphics_path_sp(const smart_pointer < graphics_path > & p) :
         smart_pointer < graphics_path > (p)
      {
      }

      graphics_path_sp(allocatorsp allocer) :
         smart_pointer < graphics_path > (allocer)
      {
      }

   };


} // namespace ca
