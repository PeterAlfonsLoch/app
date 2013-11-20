#include "framework.h"
#include "spa_window.h"
#include "spa2.h"


#ifdef LINUX
#include "boot/linux/ca_os_cross_win_gdi_internal.h"
#endif


CHAR szTitle[1024];					// The title bar text
CHAR szWindowClassSpaAdmin[1024];			// the main window class name


#define ID_CONTROL_BOX_CLOSE 31000
#define ID_CONTROL_BOX_MINIMIZE 31001

#define TIMER_CARET 123454
#define TIMER_ANIMATION 1234508
#define CARET_TIME 1000


namespace spa_install
{


   window_map window::s_windowmap;


   window::window(sp(base_application) papp) :
      element(papp),
      m_canvas(papp)
   {

      m_bDrag = false;
      m_oswindow = NULL;

   }


   window::~window()
   {
   }

   void window::PaintOpaqueBk(::draw2d::graphics * pgraphics)
   {
      RECT rectClient;

#ifdef WINDOWSEX
      ::GetClientRect(m_oswindow, &rectClient);
#else
      throw "todo";
#endif

      /*   ::FillRect(hdc, &rectClient, g_hbrushBkBorder1);

      rectClient.left += 1;
      rectClient.top += 1;
      rectClient.bottom -= 1;
      rectClient.right -= 1;
      ::FillRect(hdc, &rectClient, g_hbrushBkBorder2);
      rectClient.left += 22;
      rectClient.top += 22;
      rectClient.bottom -= 22;
      rectClient.right -= 22;*/
      pgraphics->FillRect(&rectClient, m_sbrushBk);
   }


   void window::PaintTransparentBk(::draw2d::graphics * pgraphics)
   {

#ifdef WINDOWSEX

      RECT rectWindow;


      ::GetWindowRect(m_oswindow, &rectWindow);

      ::draw2d::graphics_sp gScreen(allocer());

      throw todo(get_app());

//      if(!gScreen.create_from_screen())
  //       return;

    //  pgraphics->bit_blt(0, 0, 800, 584, gScreen, rectWindow.left, rectWindow.top, SRCCOPY);

/*      BLENDFUNCTION bf;

      bf.BlendOp             = AC_SRC_OVER;						// Only works with a 32bpp bitmap
      bf.BlendFlags          = 0;									// Always 0
      bf.SourceConstantAlpha = 255;									// set to 255 for per-pixel alpha values
      bf.AlphaFormat         = AC_SRC_ALPHA;						// Only works when the bitmap contains an alpha channel

      gScreen.alpha_blend(0, 0, 800, 584, m_sgraphicsAlpha, 0, 0, 800, 584, bf);*/

      throw todo(get_app());

      //gScreen.bit_blt(0, 0, 800, 584, m_sgraphicsAlpha, 0, 0, SRCCOPY);

#else

      throw "todo";

#endif
   }



   void window::PaintBk(::draw2d::graphics * pgraphics)
   {
      if(m_iStyle == 0)
      {
         PaintOpaqueBk(pgraphics);
      }
      else
      {
         PaintTransparentBk(pgraphics);
      }
   }


   void window::OnPaint(::draw2d::graphics * pgraphics, LPRECT lprect)
   {

#ifdef WINDOWSEX
      RECT rectWindow;
      ::GetWindowRect(m_oswindow, &rectWindow);


      int32_t cx = rectWindow.right - rectWindow.left;
      int32_t cy = rectWindow.bottom - rectWindow.top;

      RECT rect;
      rect.left         = 0;
      rect.top          = 0;
      rect.right        = cx;
      rect.bottom       = cy;

      if(lprect == NULL)
      {
         lprect = &rect;
      }

      throw todo(get_app());

/*      ::draw2d::bitmap_sp b;

      if(!b.create(cx, cy, pgraphics))
         return;

      simple_graphics g;

      if(!pgraphics->create_from_bitmap(b))
         return;*/

      PaintBk(pgraphics);

//      HFONT hfontOld = NULL;
//      HFONT hfont = NULL;

//      m_canvas.on_paint(g, &rect);


      pgraphics->SetViewportOrg(0, 0);

      //pgraphics.bit_blt(lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top, g, lprect->left, lprect->top, SRCCOPY);
#else
      throw "todo";
#endif
   }


   void window::OnPaint()
   {
      #ifdef WINDOWSEX

  //    ::draw2d::graphics_sp pgraphics(allocer());

//      RECT rcPaint;

//      if(!pgraphics.from_window_paint(m_oswindow, &rcPaint))
  //       return;

    //  OnPaint(pgraphics, &rcPaint);

#else

      throw "todo";
#endif

   }

#ifdef WINDOWS

   void window::OnTimer(uint_ptr nIDEvent)
   {

      if(nIDEvent == 184)
      {

#ifdef WINDOWSEX
/*         simple_graphics pgraphics;

         pgraphics.from_entire_window(m_oswindow);

         OnPaint(pgraphics, NULL);*/
#else
         throw "todo";

#endif
      }

   }

   LRESULT window::window_proc(UINT message, WPARAM wparam, LPARAM lparam)
   {
      switch (message)
      {
      case WM_CREATE:
         {
#ifdef WINDOWSEX
            ::SetTimer(m_oswindow, TIMER_CARET, 100, NULL);
            ::SetTimer(m_oswindow, TIMER_ANIMATION, 33, NULL);
#else
         throw "todo";

#endif
         }
         break;
      case WM_PAINT:
         OnPaint();
         break;
      case WM_ERASEBKGND:
         return TRUE;
      case WM_MBUTTONDOWN:
      case WM_RBUTTONDOWN:
         m_canvas.m_iMode++;
         return TRUE;
      case WM_LBUTTONDOWN:
         {
            m_canvas.m_iMode++;
            m_bDrag = true;
            ::GetCursorPos(&m_ptDragStart);
#ifdef WINDOWSEX
            ::GetWindowRect(m_oswindow, &m_rectWindowDragStart);
#else
            throw "todo";
#endif
         };
         break;
      case WM_MOUSEMOVE:
         {
            if(m_bDrag)
            {
               drag();
            }
         };
         break;
      case WM_LBUTTONUP:
         {
            if(m_bDrag)
            {
               drag();
               m_bDrag = false;
            }
         };
         break;

      case WM_DESTROY:
#ifdef WINDOWSEX
         PostQuitMessage(0);
#else
            throw "todo";
#endif
         break;
      case WM_TIMER:
         OnTimer(wparam);
         break;
      default:
#ifdef WINDOWSEX
         return DefWindowProc(m_oswindow, message, wparam, lparam);
#else
            throw "todo";
#endif
      }
      return 0;
   }

   LRESULT CALLBACK window::s_window_proc(oswindow oswindow, UINT message, WPARAM wParam, LPARAM lParam)
   {
      window * pwindow = s_windowmap[oswindow];
      if(pwindow != NULL)
         return pwindow->window_proc(message, wParam, lParam);
#ifdef WINDOWSEX
      return DefWindowProc(oswindow, message, wParam, lParam);
#else
            throw "todo";
#endif
   }


   ATOM window::register_class(HINSTANCE hInstance)
   {
#ifdef WINDOWSEX
      WNDCLASSEX wcex;

      wcex.cbSize = sizeof(WNDCLASSEX);

      wcex.style			   = 0;
      wcex.lpfnWndProc	   = &window::s_window_proc;
      wcex.cbClsExtra	   = 0;
      wcex.cbWndExtra	   = 0;
      wcex.hInstance		   = hInstance;
      //	wcex.hIcon			   = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CA2_SPA));
      //wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
      wcex.hIcon			   = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CA2_SPA));
      wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
      wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
      //wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CA2_SPA);
      wcex.lpszMenuName	   = NULL;
      wcex.lpszClassName	= "spa_main_window";
      wcex.hIconSm		   = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_CA2_SPA));

      return RegisterClassEx(&wcex);
#else
            throw "todo";
#endif
   }
#endif

   void window::drag()
   {
      POINT ptCursor;
      ::GetCursorPos(&ptCursor);
#ifdef WINDOWSEX

      ::SetWindowPos(m_oswindow, NULL,
         ptCursor.x - m_ptDragStart.x + m_rectWindowDragStart.left,
         ptCursor.y - m_ptDragStart.y + m_rectWindowDragStart.top,
         0,
         0,
         SWP_NOSIZE | SWP_SHOWWINDOW);
#else
            throw "todo";
#endif

      if(m_iStyle == 0)

      {
      }
      else
      {
#ifdef WINDOWSEX
         ::SetLayeredWindowAttributes(m_oswindow, 0, (255 * 100) / 100, LWA_ALPHA);
#endif
      }
#ifdef WINDOWSEX

      ::RedrawWindow(m_oswindow, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
#else
            throw "todo";
#endif
   }

   void window::redraw()
   {
#ifdef WINDOWSEX
      if(!::IsIconic(m_oswindow) && IsWindowVisible(m_oswindow))
      {
         ::RedrawWindow(m_oswindow, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
      }
#else
            throw "todo";
#endif
   }


} // namespace spa_install



