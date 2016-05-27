
BOOL window_opengl::CreateHGLRC(HWND hWnd)
{

   PIXELFORMATDESCRIPTOR pfd = {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,                                // Version Number
      PFD_DRAW_TO_WINDOW |         // Format Must Support Window
      PFD_SUPPORT_OPENGL |         // Format Must Support OpenGL
      PFD_SUPPORT_COMPOSITION |         // Format Must Support Composition
      PFD_DOUBLEBUFFER,                 // Must Support Double Buffering
      PFD_TYPE_RGBA,                    // Request An RGBA Format
      32,                               // Select Our Color Depth
      0, 0, 0, 0, 0, 0,                 // Color Bits Ignored
      8,                                // An Alpha Buffer
      0,                                // Shift Bit Ignored
      0,                                // No Accumulation Buffer
      0, 0, 0, 0,                       // Accumulation Bits Ignored
      24,                               // 16Bit Z-Buffer (Depth Buffer)
      8,                                // Some Stencil Buffer
      0,                                // No Auxiliary Buffer
      PFD_MAIN_PLANE,                   // Main Drawing Layer
      0,                                // Reserved
      0, 0, 0                           // Layer Masks Ignored
   };

   HDC hdc = GetDC(hWnd);
   int PixelFormat = ChoosePixelFormat(hdc, &pfd);
   if (PixelFormat == 0) {
      ASSERT(0);
      return FALSE;
   }

   BOOL bResult = SetPixelFormat(hdc, PixelFormat, &pfd);
   if (bResult == FALSE) {
      ASSERT(0);
      return FALSE;
   }

   m_hrc = wglCreateContext(hdc);
   if (!m_hrc) {
      ASSERT(0);
      return FALSE;
   }

   ReleaseDC(hWnd, hdc);

   return TRUE;

}





void window_opengl::on_create_window(oswindow wnd)
{

   BOOL bOk = CreateHGLRC(wnd);

   if (!bOk)
   {

      throw simple_exception(get_app(), "failed to composite");;

   }

}



//#include "framework.h"
//#include "windows_window_gdi.h"


window_opengl::window_opengl(::aura::application * papp) :
   object(papp),
   window_graphics(papp)
{

   m_hrc = NULL;

}


window_opengl::~window_opengl()
{

}


void window_opengl::create_window_graphics(oswindow interaction_impl, int64_t cxParam, int64_t cyParam, int iStrideParam)
{

   destroy_window_graphics();

   cx = cxParam;

   cy = cyParam;

   scan = 0;

}




void window_opengl::destroy_window_graphics()
{


   window_graphics::destroy_window_graphics();


}


void window_opengl::update_window(COLORREF * pcolorref, const RECT & rect, int cxParam, int cyParam, int iStride, bool bTransferBuffer)
{

   if (width(rect) <= 0 || height(rect) <= 0)
      return;

   //if(cxParam < 800)
   //{
   //   memset(pcolorref,128,iStride * cyParam);

   //}


}



