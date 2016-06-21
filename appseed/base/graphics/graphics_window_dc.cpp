#include "framework.h"
#include "graphics_window_buffer.h"


window_dc::window_dc(::aura::application * papp) :
   object(papp),
   window_graphics(papp)
{

}


window_dc::~window_dc()
{

}



::draw2d::graphics * window_dc::on_begin_draw()
{

   if (m_spgraphics.is_null())
   {

      m_spgraphics.alloc(allocer());

   }

   if (m_spgraphics->get_os_data() == NULL)
   {

      bool bOk = m_spgraphics->CreateWindowDC(m_pimpl->m_oswindow);

      if (!bOk)
      {

         throw simple_exception(get_app(), "failed to composite");;

      }

   }

   m_spgraphics->on_begin_draw(m_pimpl->m_oswindow, m_pimpl->m_rectParentClient.size());

   return m_spgraphics;

}


void window_dc::update_window()
{

   m_spgraphics->on_end_draw(m_pimpl->m_oswindow);

}


