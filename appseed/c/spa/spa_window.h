#pragma once


namespace spa
{


   class installer;
   class window;


   class CLASS_DECL_c window_map :
      public simple_map < HWND, window * >
   {


   };

   class CLASS_DECL_c window
   {
   public:


      HINSTANCE            m_hinstance;
      canvas               m_canvas;

      HWND                 m_hwnd;
      simple_brush         m_sbrushBk;
      simple_bitmap        m_sbitmapAlpha;
      simple_graphics      m_sgraphicsAlpha;
      static window_map    s_windowmap;
      int                  m_iStyle;
      installer *          m_pinstaller;

      bool m_bDrag;
      POINT m_ptDragStart;
      RECT m_rectWindowDragStart;


      window();
      ~window();


      void PaintOpaqueBk(simple_graphics & g);
      void PaintTransparentBk(simple_graphics & g);
      void OnPaint(simple_graphics & g, LPRECT lprect = NULL);
      void OnPaint();
      void PaintBk(simple_graphics & g);

      void drag();

      //virtual bool init_instance(HINSTANCE hinstance, int nCmdShow);

      void redraw();

      
    #ifdef WINDOWS

      void OnTimer(uint_ptr nIDEvent);
      static LRESULT CALLBACK s_window_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
      LRESULT window_proc(UINT message, WPARAM wParam, LPARAM lParam);
      ATOM register_class(HINSTANCE hInstance);

    #endif


      
      


   };


} // namespace spa
