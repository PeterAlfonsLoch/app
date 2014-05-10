#pragma once


namespace user
{


   class CLASS_DECL_CORE elastic_slider :
      public ::user::interaction

   {
   public:



      double_scalar  m_scalarVelocity;
      double_scalar  m_scalarPosition;

      e_scalar       m_escalar;

      uint32_t       m_dwLastTime;

      double         m_dPosition;// 0.0 = min 1.0 = max
      double         m_dTensionPosition;// 0.0 = min 1.0 = max
      bool           m_bSlide;
      index          m_iScalar;
      double_array   m_daScalar;

      elastic_slider(sp(::base::application) papp);
      virtual ~elastic_slider();


      virtual void install_message_handling(::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      void Slide();




      void SetStreamingVelocityMode(double_scalar & scalarVelocity, double_scalar & scalarPosition);


      void UpdatePosition();
      void CalcTension(point & pt);
      void SetSliderPos(double dPos);

      double CalcScalar();
      void CalcTension();


      virtual void _001OnDraw(::draw2d::graphics * pdc);

      double GetForce();

      void GetSliderRect(rect & rect);

   };

} // namespace user