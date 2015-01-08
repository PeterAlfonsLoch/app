#pragma once


namespace user
{


   class CLASS_DECL_CORE slider:
      public ::user::interaction
   {
   public:


      scalar_base *  m_pscalar;

      double         m_dRate;

      bool           m_bSlide;

      


      slider(::aura::application * papp);
      virtual ~slider();


      virtual void install_message_handling(::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);

      void set_scalar(scalar_base * pscalar);

      void set_rate(double dRate);

      double get_slide_rate();

      virtual void _001OnDraw(::draw2d::graphics * pdc);

      void get_slider_rect(rect & rect);

   };


} // namespace user




































































