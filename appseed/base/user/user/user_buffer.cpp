#include "framework.h"

namespace user
{

   buffer::buffer(sp(::base::application) papp) :
      element(papp),
      m_spdib(allocer())
   {
   }

   buffer::~buffer()
   {
      clear();
   }

   bool buffer::clear()
   {
      m_spdib->Destroy();
      return true;
   }

   bool buffer::UpdateBuffer(size size)
   {
      return UpdateBuffer(size.cx, size.cy);
   }

   bool buffer::UpdateBuffer(class point point)
   {
      return UpdateBuffer(point.x, point.y);
   }

   bool buffer::UpdateBuffer(int32_t cx, int32_t cy)
   {
      m_size.cx = cy;
      m_size.cy = cy;
      if(!m_spdib->create(cx, cy))
         return false;
      m_spdib->get_graphics()->SetViewportOrg(
         0,
         0);
      //m_spdib->get_graphics()->SelectClipRgn(NULL);
      return true;
   }

   critical_section * buffer::GetSemaphore()
   {
      return &m_semaphoreBuffer;
   }

   ::draw2d::graphics * buffer::GetBuffer()
   {
      return m_spdib->get_graphics();
   }

   void buffer::InstallMessageHandling(::message::dispatch *pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
   }


   void buffer::BitBlt(::draw2d::graphics * pdc)
   {

      pdc->BitBlt(null_point(), m_spdib->size(), GetBuffer());

   }


   void buffer::BitBlt(LPRECT lprect, ::draw2d::graphics * pdc)
   {

      pdc->BitBlt(*lprect, GetBuffer(), top_left(lprect));

   }


} // namespace user

