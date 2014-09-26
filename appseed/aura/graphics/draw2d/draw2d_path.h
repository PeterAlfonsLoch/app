#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA path :
      virtual public ::draw2d::object
   {
   public:


     class CLASS_DECL_AURA arc
      {
      public:


         double   m_xCenter;
         double   m_yCenter;
         double   m_dRadiusX;
         double   m_dRadiusY;
         double   m_dAngle1;
         double   m_dAngle2;


      };

      class CLASS_DECL_AURA move
      {
      public:

         double   m_x;
         double   m_y;

      };


      class CLASS_DECL_AURA line
      {
      public:

         double   m_x;
         double   m_y;

      };

      class CLASS_DECL_AURA end
      {
      public:

         bool     m_bClose;

      };

      class CLASS_DECL_AURA string_path
      {
      public:

         double               m_x;
         double               m_y;
         string               m_strText;
         ::draw2d::font_sp    m_spfont;

         string_path();
         string_path(const string_path & stringpath);
         ~string_path();

         string_path & operator = (const string_path & stringpath);

      };

      class CLASS_DECL_AURA element :
      virtual public ::object
      {
      public:


            enum e_type
            {
               type_none,
               type_begin,
               type_arc,
               type_line,
               type_move,
               type_string,
               type_end
                  
            };


            union
            {


               arc      m_arc;
               move     m_move;
               line     m_line;
               end      m_end;

            } u;

            string_path m_stringpath;

            e_type m_etype;

            element();
            element(const element & e);
            ~element();

            element & operator = (const element & e);

      };


      spa(element)                     m_elementa;
      bool                             m_bFill;
      ::draw2d::e_fill_mode            m_efillmode;
      bool                             m_bHasPoint;
      pointd                           m_pt;


      path();
      path(::aura::application * papp);
      virtual ~path();


      virtual bool has_current_point();
      virtual pointd last_point();



      virtual bool begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      virtual bool end_figure(bool bClose);


      //virtual bool is_empty();
      //virtual bool has_current_point();
      //virtual point current_point();

      virtual bool add_arc(const RECT & rect, int32_t iStart, int32_t iAngle);

      using ::draw2d::object::add_line;
      virtual bool add_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool add_line(double x1,double y1,double x2,double y2);
      virtual bool add_line(point p1, point p2);

      virtual bool add_lines(const POINT * lppoint, int32_t nCount);
      virtual bool add_lines(const POINTD * lppoint,int32_t nCount);

      virtual bool add_line(int32_t x, int32_t y);
      virtual bool add_line(double x,double y);
      virtual bool add_line(point p);
      virtual bool add_line(pointd p);

      virtual bool add_move(double x,double y);
      virtual bool add_move(pointd p);
      virtual bool add_move(int32_t x, int32_t y);
      virtual bool add_move(point p);

      virtual bool add_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
      virtual bool add_rect(const RECT & rect);
      virtual bool add_rect(LPCRECT lpcrect);


      virtual bool add_string(int32_t x,int32_t y,const string & strText,::draw2d::font_sp spfont);

      virtual void * detach();


      virtual void get_bounding_rect(LPRECT lprect);
      virtual void get_bounding_rect(LPRECT lprect,element & e);
      virtual void get_bounding_rect(LPRECT lprect,arc & a);
      virtual void get_bounding_rect(LPRECT lprect,move & m);
      virtual void get_bounding_rect(LPRECT lprect,line & l);
      virtual void get_bounding_rect(LPRECT lprect,string_path & p);


      //=============================================================================
      //
      // get_round_rect()
      //
      // Purpose:     Defines a Rounded Rectangle and places it in the GraphicsPath
      //
      // Parameters:  pPath		- [out] pointer to GraphicsPath that will recieve the
      //									path data
      //				r			- [in]	Rect that defines the round rectangle boundaries
      //				dia			- [in]	diameter of the rounded corners (2*radius)
      //
      // Returns:     None
      //
      bool add_round_rect(const RECT & rect, int32_t dia);
      bool add_round_top_left(const RECT & rect, int32_t dia);
      bool add_round_bottom_right(const RECT & rect, int32_t dia);




   };


   class CLASS_DECL_AURA path_sp :
      public smart_pointer < path >
   {
   public:

      path_sp()
      {
      }

      path_sp(const smart_pointer < path > & p) :
         smart_pointer < path > (p)
      {
      }

      path_sp(allocatorsp allocer) :
         smart_pointer < path > (allocer)
      {
      }

      path_sp & operator = (::draw2d::path * ppath)
      {

         smart_pointer < path >::operator = (ppath);
         
         return *this;
         
      }


   };


} // namespace draw2d






