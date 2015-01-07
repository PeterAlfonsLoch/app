#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D graphics_path :
      virtual public ::draw2d::path,
      virtual public ::draw2d::object
   {
   public:

      //struct PathTextDrawingContext
      //{

      //   graphics_path * m_pthis;
      //   ID2D1GeometrySink* psink;
      //};


      Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_ppath;
      Microsoft::WRL::ComPtr<ID2D1GeometrySink>        m_psink;
      bool                       m_bFigureEnded;


      graphics_path(::aura::application * papp);
      virtual ~graphics_path();


      virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);


      //virtual bool is_empty();
      //virtual bool has_current_point();
      //virtual point current_point();

      virtual bool internal_add_arc(const RECT & rect, double dStart, double dEnd);

      virtual bool internal_add_line(int x1, int y1, int x2, int y2);
      
      virtual bool internal_add_rect(int x,int y,int cx,int cy);

      virtual bool internal_add_line(int x, int y);

      virtual bool internal_add_move(int x, int y);


      virtual bool internal_add_string(::draw2d_direct2d::graphics * pdc,int32_t x,int32_t y,const string & strText,::draw2d::font_sp spfont);

      virtual bool internal_prepare(D2D1_POINT_2F pt);
      virtual bool internal_get_arc(D2D1_POINT_2F & pt, D2D1_ARC_SEGMENT & arcseg, const RECT & rect, double dStart,double dEnd);

      //virtual bool internal_add_rect(int x1, int y1, int x2, int y2);

      virtual void * get_os_data() const;
      virtual void * detach();

      ID2D1PathGeometry * get_os_path(::draw2d_direct2d::graphics * pdc);

      virtual bool create();
      bool destroy();
      bool set(::draw2d_direct2d::graphics * pdc,const ::draw2d::path::element & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::move & move);
      bool set(const ::draw2d::path::line & line);
      bool set(const ::draw2d::path::rect & rect);
      bool set(::draw2d_direct2d::graphics * pdc,const ::draw2d::path::string_path & path);

      static void CreatePathTextRenderer(FLOAT pixelsPerDip,IDWriteTextRenderer **textRenderer);


   };


} // namespace draw2d_direct2d



