#include "framework.h"


window_graphics::window_graphics(::aura::application * papp) :
   object(papp)
{

   m_cx = 0;
   m_cy = 0;
   defer_create_mutex();

}


window_graphics::~window_graphics()
{

   destroy_buffer();

   destroy_window_graphics_();

   

}


void window_graphics::on_create_window(::user::interaction_impl * pimpl)
{
   
   m_pimpl = pimpl;

}


void window_graphics::create_window_graphics_(int64_t cxParam, int64_t cyParam, int iStride)
{

}


void window_graphics::destroy_window_graphics_()
{

}


void window_graphics::create_buffer(int64_t cxParam, int64_t cyParam, int iStride)
{

   m_cx = (int32_t)cxParam;
   m_cy = (int32_t)cyParam;
   m_iScan = (int32_t)iStride;

}


void window_graphics::destroy_buffer()
{

   m_cx = 0;
   m_cy = 0;

}


void window_graphics::update_window()
{

}


::draw2d::graphics * window_graphics::on_begin_draw()
{

   return NULL;

}



