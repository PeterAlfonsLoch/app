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

      output_debug_string("window_buffer m_spdibBuffer NULL");

      m_spdibBuffer.alloc(allocer());

   }

   if(!m_spdibBuffer->create(m_pimpl->m_rectParentClient.size()))
   {

      output_debug_string("window_buffer create (width=" + ::str::from(width(m_pimpl->m_rectParentClient)) + ",height=" + ::str::from(height(m_pimpl->m_rectParentClient)) + ")");

      return NULL;

   }

   if (m_cx != m_pimpl->m_rectParentClient.size().cx || m_cy != m_pimpl->m_rectParentClient.size().cy)
   {

      create_window_graphics(m_pimpl->m_rectParentClient.size().cx, m_pimpl->m_rectParentClient.size().cy, m_spdibBuffer->m_iScan);

   }

   return m_spdibBuffer->get_graphics();

}







window_double_buffer::window_double_buffer(::aura::application * papp) :
   object(papp),
   window_graphics(papp),
   window_buffer(papp),
   m_mutex2(papp),
   m_spdibBuffer2(allocer())
{
   
}


window_double_buffer::~window_double_buffer()
{

}


void window_double_buffer::update_window()
{

   synch_lock sl(&m_mutex2);

   m_spdibBuffer2->from(m_spdibBuffer);

}
