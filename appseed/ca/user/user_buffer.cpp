#include "framework.h"

namespace user
{

   buffer::buffer(::ca::application * papp) :
      ca(papp),
      m_spdib(papp)
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

   bool buffer::UpdateBuffer(class size size)
   {
      return UpdateBuffer(size.cx, size.cy);
   }

   bool buffer::UpdateBuffer(class point point)
   {
      return UpdateBuffer(point.x, point.y);
   }

   bool buffer::UpdateBuffer(int cx, int cy)
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

   ::ca::graphics * buffer::GetBuffer()
   {
      return m_spdib->get_graphics();
   }

   void buffer::InstallMessageHandling(::gen::message::dispatch *pinterface)
   {
      UNREFERENCED_PARAMETER(pinterface);
   }

   void buffer::BitBlt(::ca::graphics * pdc)
   {
      pdc->BitBlt(
         0, 0, 
         m_spdib->width(),
         m_spdib->height(),
         GetBuffer(),
         0, 0, 
         SRCCOPY);
   }

   void buffer::BitBlt(LPRECT lprect, ::ca::graphics * pdc)
   {
      pdc->BitBlt(
         lprect->left, lprect->top, 
         lprect->right - lprect->left,
         lprect->bottom - lprect->top,
         GetBuffer(),
         lprect->left, lprect->top, 
         SRCCOPY);
   }

} // namespace user

