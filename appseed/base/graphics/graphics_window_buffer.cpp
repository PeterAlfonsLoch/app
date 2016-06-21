#include "framework.h"
#include "graphics_window_buffer.h"


window_buffer::window_buffer(::aura::application * papp) :
   object(papp),
   window_graphics(papp)
{

}


window_buffer::~window_buffer()
{

}


void window_buffer::create_window_graphics(oswindow interaction_impl, int64_t cxParam, int64_t cyParam, int iStrideParam)
{

   destroy_window_graphics();

   if(interaction_impl == NULL)
      return;

   m_hwnd = interaction_impl;

   window_graphics::create_window_graphics(interaction_impl, cxParam, cyParam, iStrideParam);

}




void window_buffer::destroy_window_graphics()
{

   m_hwnd = NULL;

   window_graphics::destroy_window_graphics();


}


void window_buffer::update_window()
{

   update_window(m_spdibBuffer->get_data(), m_spdibBuffer->m_size.cx, m_spdibBuffer->m_size.cy, m_spdibBuffer->m_iScan);

}




void window_buffer::update_window(COLORREF * pcolorref,int cxParam,int cyParam,int iStride)
{

   UNREFERENCED_PARAMETER(pcolorref);
   UNREFERENCED_PARAMETER(cxParam);
   UNREFERENCED_PARAMETER(cyParam);
   UNREFERENCED_PARAMETER(iStride);

}


::draw2d::graphics * window_buffer::on_begin_draw()
{

   if (m_spdibBuffer.is_null())
   {

      m_spdibBuffer.alloc(allocer());

   }

   if(!m_spdibBuffer->create(m_pimpl->m_rectParentClient.size()))
   {

      return NULL;

   }

   if (m_hwnd != m_pimpl->m_oswindow || cx != m_pimpl->m_rectParentClient.size().cx || cy != m_pimpl->m_rectParentClient.size().cy)
   {

      create_window_graphics(m_pimpl->m_oswindow, m_pimpl->m_rectParentClient.size().cx, m_pimpl->m_rectParentClient.size().cy, m_spdibBuffer->m_iScan);

   }

   return m_spdibBuffer->get_graphics();

}



