#pragma once

#include "multithreading/multithreading.h"


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

      void InstallMessageHandling(win::message::dispatch * pinterface);


      bool UpdateBuffer(int cx, int cy);
      bool UpdateBuffer(class size size);
      bool UpdateBuffer(class point point);
      ::ca::graphics * GetBuffer();
      ::critical_section * GetSemaphore();
      bool clear();

      ::ca::dib_sp               m_spdib;
   protected:
      ::critical_section         m_semaphoreBuffer;
      size                       m_size;

   };

} // namespace visual

