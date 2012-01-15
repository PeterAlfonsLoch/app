#include "StdAfx.h"


#ifdef LINUX
#include "c/linux/c_os_cross_win_gdi_internal.h"
#endif


TCHAR szTitle[1024];					// The title bar text
TCHAR szWindowClassSpaAdmin[1024];			// the main window class name


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
      m_hbrushBk = NULL;
      m_bDrag = false;
      m_hwnd = NULL;
   }

   window::~window()
   {
   }

   void window::PaintOpaqueBk(HDC hdc)
   {
      RECT rectClient;

      ::GetClientRect(m_hwnd, &rectClient);

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
      ::FillRect(hdc, &rectClient, m_hbrushBk);
   }


void window::PaintTransparentBk(HDC hdc)
{
   
#ifdef WINDOWS
   
   RECT rectWindow;

   ::GetWindowRect(m_hwnd, &rectWindow);

   HDC hdcScreen = ::GetDC(NULL);

   ::BitBlt(hdc, 0, 0, 800, 584, hdcScreen, rectWindow.left, rectWindow.top, SRCCOPY);

   BLENDFUNCTION bf;

	bf.BlendOp             = AC_SRC_OVER;						// Only works with a 32bpp bitmap
	bf.BlendFlags          = 0;											// Always 0
	bf.SourceConstantAlpha = 255;										// Set to 255 for per-pixel alpha values
	bf.AlphaFormat         = AC_SRC_ALPHA;						// Only works when the bitmap contains an alpha channel
   ::AlphaBlend(hdc, 0, 0, 800, 584, g_hdcAlpha, 0, 0, 800, 584, bf);

   ::ReleaseDC(NULL, hdcScreen);
   
#endif
   
}



void window::PaintBk(HDC hdc)
{
   if(m_iStyle == 0)
   {
      PaintOpaqueBk(hdc);
   }
   else
   {
      PaintTransparentBk(hdc);
   }
}


void window::OnPaint(HDC hdcWindow, LPRECT lprect)
{
   RECT rectWindow;
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
   
#ifdef WINDOWS

   BITMAPINFO m_Info;

	m_Info.bmiHeader.biSize=sizeof (BITMAPINFOHEADER);
	m_Info.bmiHeader.biWidth=cx;
	m_Info.bmiHeader.biHeight=cy;
	m_Info.bmiHeader.biPlanes=1;
	m_Info.bmiHeader.biBitCount=32;
	m_Info.bmiHeader.biCompression=BI_RGB;
	m_Info.bmiHeader.biSizeImage=cx*cy*4;

   LPDWORD lpdata;

	HBITMAP hbmp = CreateDIBSection ( NULL, &m_Info, DIB_RGB_COLORS, (void **)&lpdata, NULL, 0);

   //HBITMAP hbmp      = ::CreateCompatibleBitmap(hdcWindow, cx, cy);
   HDC hdc           = ::CreateCompatibleDC(NULL);
   HBITMAP hbmpOld   =  (HBITMAP) ::SelectObject(hdc, (HGDIOBJ) hbmp);

   //::BitBlt(hdc, 0, 0, cx, cy, hdcWindow, 0, 0, SRCCOPY);

   PaintBk(hdc);

   HFONT hfontOld = NULL;
   HFONT hfont = NULL;
   
#else
   
   HDC hdc = hdcWindow;
   
#endif
   

   m_canvas.on_paint(hdc, &rect);


#ifdef WINDOWS
   
   POINT pointViewport;
   ::SetViewportOrgEx(hdc, 0, 0, &pointViewport);
   ::BitBlt(hdcWindow, lprect->left, lprect->top, lprect->right - lprect->left, lprect->bottom - lprect->top,
            hdc,       lprect->left, lprect->top, SRCCOPY);
   ::SelectObject(hdc, (HGDIOBJ) hbmpOld);
   if(hfontOld != NULL)
   {
      ::SelectObject(hdc,(HGDIOBJ)  hfontOld);
   }
   if(hfont != NULL)
   {
      ::DeleteObject(hfont);
   }
   ::DeleteObject(hbmp);
   ::DeleteDC(hdc);
   
#endif
   
}


void window::OnPaint()
{

	PAINTSTRUCT ps;
	HDC hdcWindow;
	hdcWindow = BeginPaint(m_hwnd, &ps);
   OnPaint(hdcWindow, &ps.rcPaint);
	EndPaint(m_hwnd, &ps);

}

   void window::OnTimer(UINT nIDEvent)
   {
      if(nIDEvent == 184)
      {
         HDC hdc = ::GetWindowDC(m_hwnd);
         OnPaint(hdc, NULL);
         ::ReleaseDC(m_hwnd, hdc);
      }
   }

#ifdef WINDOWS
   LRESULT window::window_proc(UINT message, WPARAM wparam, LPARAM lparam)
   {
	   switch (message)
	   {
      case WM_CREATE:
         {
            ::SetTimer(m_hwnd, TIMER_CARET, 100, NULL);
            ::SetTimer(m_hwnd, TIMER_ANIMATION, 33, NULL);
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
            ::GetWindowRect(m_hwnd, &m_rectWindowDragStart);
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
		   PostQuitMessage(0);
		   break;
      case WM_TIMER:
         OnTimer(wparam);
         break;
	   default:
		   return DefWindowProc(m_hwnd, message, wparam, lparam);
	   }
	   return 0;
   }

   LRESULT CALLBACK window::s_window_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
   {
      window * pwindow = s_windowmap[hwnd];
      if(pwindow != NULL)
         return pwindow->window_proc(message, wParam, lParam);
      return DefWindowProc(hwnd, message, wParam, lParam);
   }


   ATOM window::register_class(HINSTANCE hInstance)
   {
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
   }
#endif

   void window::drag()
   {
      POINT ptCursor;
      ::GetCursorPos(&ptCursor);
      ::SetWindowPos(m_hwnd, NULL,
         ptCursor.x - m_ptDragStart.x + m_rectWindowDragStart.left,
         ptCursor.y - m_ptDragStart.y + m_rectWindowDragStart.top,
         0,
         0,
         SWP_NOSIZE | SWP_SHOWWINDOW);
      if(m_iStyle == 0)
      {
      }
      else
      {
#ifdef WINDOWS
          ::SetLayeredWindowAttributes(m_hwnd, 0, (255 * 100) / 100, LWA_ALPHA);
#endif
      }
      ::RedrawWindow(m_hwnd, NULL, NULL, RDW_UPDATENOW | RDW_INVALIDATE);
   }

   void window::redraw()
   {
      if(!::IsIconic(m_hwnd) && IsWindowVisible(m_hwnd))
      {
         ::RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
      }
   }


} // namespace spa



