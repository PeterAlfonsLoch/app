#pragma once

namespace user
{

   class CLASS_DECL_ca2 elastic_slider :
      public ::user::interaction

   {
   public:
      elastic_slider(sp(::application) papp);
   public:
      virtual ~elastic_slider();


      virtual void install_message_handling(::ca2::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)


      void Slide();


      enum EScalar
      {
         ScalarStreamingVelocity, 
         // to the right accelerates, to left certain range,
         // slow down, to left pass certain range, rewinds.

      };


      void SetStreamingVelocityMode(DoubleScalar * pscalarVelocity, int32_t iVelocity, DoubleScalar * pscalarPosition, int32_t iPosition);

      DoubleScalar * m_pscalarVelocity;
      int32_t m_iVelocity;
      DoubleScalar * m_pscalarPosition;
      int32_t m_iPosition;

      void UpdatePosition();
      void CalcTension(point & pt);
      void SetSliderPos(double dPos);

      double CalcScalar();
      void CalcTension();


      virtual void _001OnDraw(::draw2d::graphics * pdc);

   protected:
      EScalar m_escalar;

      uint32_t m_dwLastTime;

      double m_dPos;// 0.0 = min 1.0 = max
      double m_dTensionPos;// 0.0 = min 1.0 = max
      bool m_bSlide;
      int32_t m_iScalar;
      double_array m_daScalar;
      double GetForce();

      void GetSliderRect(rect & rect);

   };

} // namespace user