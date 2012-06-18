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
      HBRUSH               m_hbrushBk;
      HBITMAP              g_hbmAlpha;
      HDC                  g_hdcAlpha;
      static window_map    s_windowmap;
      int                  m_iStyle;
      installer *          m_pinstaller;

      bool m_bDrag;
      POINT m_ptDragStart;
      RECT m_rectWindowDragStart;


      window();
      ~window();

      void PaintOpaqueBk(HDC hdc);
      void PaintTransparentBk(HDC hdc);
      void OnPaint(HDC hdcWindow, LPRECT lprect = NULL);
      void OnPaint();
      void PaintBk(HDC hdc);

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
