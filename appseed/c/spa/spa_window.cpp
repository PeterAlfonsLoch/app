#include "framework.h"


#ifdef LINUX
#include "c/linux/c_os_cross_win_gdi_internal.h"
#endif


CHAR szTitle[1024];					// The title bar text
CHAR szWindowClassSpaAdmin[1024];			// the main window class name


#define ID_CONTROL_BOX_CLOSE 31000
#define ID_CONTROL_BOX_MINIMIZE 31001

#define TIMER_CARET 123454
#define TIMER_ANIMATION 1234508
#define CARET_TIME 1000


namespace spa
{

   window_map window::s_windowmap;

   window::window()
   {
      m_bDrag = false;
      m_hwnd = NULL;
   }

   window::~window()
   {
   }

   void window::PaintOpaqueBk(simple_graphics & g)
   {
      RECT rectClient;

#ifdef WINDOWSEX
      ::GetClientRect(m_hwnd, &rectClient);
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
      g.fill_rect(&rectClient, m_sbrushBk);
   }


   void window::PaintTransparentBk(simple_graphics & g)
   {

      RECT rectWindow;

#ifdef WINDOWSEX

      ::GetWindowRect(m_hwnd, &rectWindow);

      simple_graphics gScreen;

      if(!gScreen.create_from_screen())
         return;

      g.bit_blt(0, 0, 800, 584, gScreen, rectWindow.left, rectWindow.top, SRCCOPY);

      BLENDFUNCTION bf;

      bf.BlendOp             = AC_SRC_OVER;						// Only works with a 32bpp bitmap
      bf.BlendFlags          = 0;									// Always 0
      bf.SourceConstantAlpha = 255;									// Set to 255 for per-pixel alpha values
      bf.AlphaFormat         = AC_SRC_ALPHA;						// Only works when the bitmap contains an alpha channel

      gScreen.alpha_blend(0, 0, 800, 584, m_sgraphicsAlpha, 0, 0, 800, 584, bf);
#else

#endif
   }



   void window::PaintBk(simple_graphics & g)
   {
      if(m_iStyle == 0)
      {
         PaintOpaqueBk(g);
      }
      else
      {
         PaintTransparentBk(g);
      }
   }


   void window::OnPaint(simple_graphics & gWindow, LPRECT lprect)
   {
      RECT rectWindow;

#ifdef WINDOWSEX
      ::GetWindowRect(m_hwnd, &rectWindow);


      int cx = rectWindow.right - rectWindow.left;
      int cy = rectWindow.bottom - rectWindow.top;

      RECT rect;
      rect.left         = 0;
      rect.top          = 0;
      rect.right        = cx;
      rect.bottom       = cy;

      if(lprect == NULL)
      {
         lprect = &rect;
      }

      simple_bitmap b;

      if(!b.create(cx, cy, gWindow))
         return;

      simple_graphics g;

      if(!g.create_from_bitmap(b))
         return;

      PaintBk(g);

//      HFONT hfontOld = NULL;
//      HFONT hfont = NULL;

      m_canvas.on_paint(g, &rect);


      g.set_offset(0, 0);

      gWindow.bit_blt(lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top, g, lprect->left, lprect->top, SRCCOPY);
#else
      throw "todo";
#endif
   }


   void window::OnPaint()
   {
      #ifdef WINDOWSEX

      simple_graphics gWindow;

      RECT rcPaint;

      if(!gWindow.from_window_paint(m_hwnd, &rcPaint))
         return;

      OnPaint(gWindow, &rcPaint);

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
         simple_graphics gWindow;

         gWindow.from_entire_window(m_hwnd);

         OnPaint(gWindow, NULL);
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
            ::SetTimer(m_hwnd, TIMER_CARET, 100, NULL);
            ::SetTimer(m_hwnd, TIMER_ANIMATION, 33, NULL);
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
            ::GetWindowRect(m_hwnd, &m_rectWindowDragStart);
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
         return DefWindowProc(m_hwnd, message, wparam, lparam);
#else
            throw "todo";
#endif
      }
      return 0;
   }

   LRESULT CALLBACK window::s_window_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
      window * pwindow = s_windowmap[hwnd];
      if(pwindow != NULL)
         return pwindow->window_proc(message, wParam, lParam);
#ifdef WINDOWSEX
      return DefWindowProc(hwnd, message, wParam, lParam);
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
      //	wcex.hIcon			   = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CCVOTAGUS_CA2_SPA));
      //wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
      wcex.hIcon			   = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CCVOTAGUS_CA2_SPA));
      wcex.hCursor		   = LoadCursor(NULL, IDC_ARROW);
      wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
      //wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CCVOTAGUS_CA2_SPA);
      wcex.lpszMenuName	   = NULL;
      wcex.lpszClassName	= "spa_main_window";
      wcex.hIconSm		   = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_CCVOTAGUS_CA2_SPA));

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

      ::SetWindowPos(m_hwnd, NULL,
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
         ::SetLayeredWindowAttributes(m_hwnd, 0, (255 * 100) / 100, LWA_ALPHA);
#endif
      }
#ifdef WINDOWSEX

      ::RedrawWindow(m_hwnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
#else
            throw "todo";
#endif
   }

   void window::redraw()
   {
#ifdef WINDOWSEX
      if(!::IsIconic(m_hwnd) && IsWindowVisible(m_hwnd))
      {
         ::RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
      }
#else
            throw "todo";
#endif
   }


} // namespace spa



