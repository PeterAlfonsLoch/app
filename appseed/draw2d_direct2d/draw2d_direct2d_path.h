#pragma once


namespace draw2d_direct2d
{


   class CLASS_DECL_DRAW2D_DIRECT2D graphics_path :
      virtual public ::draw2d::path,
      virtual public ::draw2d::object
   {
   public:


      Microsoft::WRL::ComPtr<ID2D1PathGeometry>        m_ppath;
      Microsoft::WRL::ComPtr<ID2D1GeometrySink>        m_psink;
      bool                       m_bFigureEnded;


      graphics_path(sp(::aura::application) papp);
      virtual ~graphics_path();


      virtual bool internal_begin_figure(bool bFill, ::draw2d::e_fill_mode efillmode);
      virtual bool internal_end_figure(bool bClose);


      //virtual bool is_empty();
      //virtual bool has_current_point();
      //virtual point current_point();

      virtual bool internal_add_arc(const RECT & rect, int iStart, int iAngle);

      virtual bool internal_add_line(int x1, int y1, int x2, int y2);

      virtual bool internal_add_line(int x, int y);

      virtual bool internal_add_move(int x, int y);

      virtual bool internal_prepare(D2D1_POINT_2F pt);
      virtual bool internal_get_arc(D2D1_POINT_2F & pt, D2D1_ARC_SEGMENT & arcseg, const RECT & rect, int iStart, int iAngle);

      //virtual bool internal_add_rect(int x1, int y1, int x2, int y2);

      virtual void * get_os_data() const;
      virtual void * detach();

      ID2D1PathGeometry * get_os_path();

      virtual bool create();
      virtual bool destroy();
      bool set(const ::draw2d::path::element & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::move & move);
      bool set(const ::draw2d::path::line & line);
      bool set(const ::draw2d::path::string_path & path);



   };


} // namespace draw2d_direct2d



