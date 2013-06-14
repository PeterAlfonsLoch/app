#pragma once


#include "base/multithreading/multithreading.h"
#include "base/ca2/ca_dib.h"


namespace user
{

   class CLASS_DECL_ca2 buffer :
      virtual public ::ca2::signalizable
   {
   public:
      buffer(sp(::ca2::application) papp);
      virtual ~buffer();

      void BitBlt(::ca2::graphics * pdc);
      void BitBlt(LPRECT lprect, ::ca2::graphics * pdc);

      void InstallMessageHandling(::ca2::message::dispatch * pinterface);


      bool UpdateBuffer(int32_t cx, int32_t cy);
      bool UpdateBuffer(class size size);
      bool UpdateBuffer(class point point);
      ::ca2::graphics * GetBuffer();
      ::critical_section * GetSemaphore();
      bool clear();

      ::ca2::dib_sp               m_spdib;
   protected:
      ::critical_section         m_semaphoreBuffer;
      size                       m_size;

   };

} // namespace visual

