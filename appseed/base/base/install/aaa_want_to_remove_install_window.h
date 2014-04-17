#pragma once



namespace install
{


   class CLASS_DECL_BASE window :
      virtual public ::base::os::simple_ui
   {
   public:


      HINSTANCE               m_hinstance;
      canvas                  m_canvas;

      oswindow                m_oswindow;
      ::draw2d::brush_sp      m_sbrushBk;
      ::draw2d::bitmap_sp     m_sbitmapAlpha;
      ::draw2d::graphics_sp   m_sgraphicsAlpha;
      static window_map       s_windowmap;
      int32_t                 m_iStyle;
      installer *             m_pinstaller;

      bool                    m_bDrag;
      POINT                   m_ptDragStart;
      RECT                    m_rectWindowDragStart;


      window(sp(base_application) papp);
      ~window();


      void PaintOpaqueBk(::draw2d::graphics * pgraphics);
      void PaintTransparentBk(::draw2d::graphics * pgraphics);
      void OnPaint(::draw2d::graphics * pgraphics, LPRECT lprect = NULL);
      void OnPaint();
      void PaintBk(::draw2d::graphics * pgraphics);

      void drag();

      //virtual bool init_instance(HINSTANCE hinstance, int32_t nCmdShow);

      void redraw();

      
    #ifdef WINDOWS

      void OnTimer(uint_ptr nIDEvent);
      static LRESULT CALLBACK s_window_proc(oswindow oswindow, UINT message, WPARAM wParam, LPARAM lParam);
      LRESULT window_proc(UINT message, WPARAM wParam, LPARAM lParam);
      ATOM register_class(HINSTANCE hInstance);

    #endif


      
      


   };


} // namespace install
