#pragma once



namespace user
{


   class CLASS_DECL_AXIS buffer :
      virtual public signalizable
   {
   public:
      buffer(sp(::base::application) papp);
      virtual ~buffer();

      void BitBlt(::draw2d::graphics * pdc);
      void BitBlt(LPRECT lprect, ::draw2d::graphics * pdc);

      void InstallMessageHandling(::message::dispatch * pinterface);


      bool UpdateBuffer(int32_t cx, int32_t cy);
      bool UpdateBuffer(class size size);
      bool UpdateBuffer(class point point);
      ::draw2d::graphics * GetBuffer();
      ::critical_section * GetSemaphore();
      bool clear();

      ::draw2d::dib_sp               m_spdib;
   protected:
      ::critical_section         m_semaphoreBuffer;
      size                       m_size;


   };


} // namespace visual




