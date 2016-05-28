





void window_opengl::on_create_window(oswindow wnd)
{

//   m_hwnd = wnd;

}



//#include "framework.h"
//#include "windows_window_gdi.h"


window_opengl::window_opengl(::aura::application * papp) :
   object(papp),
   window_graphics(papp)
{

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


//void window_opengl::update_window(COLORREF * pcolorref, int cxParam, int cyParam, int iStride)
//{
//
//   if (width(rect) <= 0 || height(rect) <= 0)
//      return;
//
//   //if(cxParam < 800)
//   //{
//   //   memset(pcolorref,128,iStride * cyParam);
//
//   //}
//
//
//}

::draw2d::graphics * window_opengl::on_begin_draw(oswindow wnd, SIZE sz)
{

 
   if (m_spgraphics.is_null())
   {

      m_spgraphics.alloc(allocer());

   }

   if(m_spgraphics->get_os_data() == NULL)
   {

      m_hwnd = wnd;


      bool bOk = m_spgraphics->CreateWindowDC(wnd);

      if (!bOk)
      {

         throw simple_exception(get_app(), "failed to composite");;

      }

   }

   m_spgraphics->on_begin_draw(wnd, sz);

   //if (m_spgraphics->get_os_data() == NULL)
   //{

   //   m_spgraphics->CreateWindowDC(wnd);

   //}
   //
   return m_spgraphics;

}


void window_opengl::update_window()
{

   m_spgraphics->on_end_draw(m_hwnd);

}


