#pragma once


#include "multithreading/multithreading.h"
#include "ca/ca/ca_dib.h"


namespace user
{

   class CLASS_DECL_ca buffer : 
      virtual public gen::signalizable
   {
   public:
      buffer(::ca::application * papp);
      virtual ~buffer();

      void BitBlt(::ca::graphics * pdc);
      void BitBlt(LPRECT lprect, ::ca::graphics * pdc);

      void InstallMessageHandling(gen::message::dispatch * pinterface);


      bool UpdateBuffer(::ca::graphics * pdc, int cx, int cy);
      bool UpdateBuffer(::ca::graphics * pdc, class size size);
      bool UpdateBuffer(::ca::graphics * pdc, class point point);
      ::ca::graphics * GetBuffer();
      ::critical_section * GetSemaphore();
      bool clear();

      ::ca::dib_sp               m_spdib;
   protected:
      ::critical_section         m_semaphoreBuffer;
      size                       m_size;

   };

} // namespace visual

