#pragma once

namespace user
{


   class CLASS_DECL_ca2 step_slider :
      public ::user::interaction
   {
   public:


      int32_t            m_iScalar;
      IntScalar *    m_pscalar;


   protected:
      
      
      bool        m_bHover;
      int32_t         m_iHover;
      int32_t         m_iLButtonDown;


   public:
      step_slider(sp(::ca::application) papp);
      virtual ~step_slider();

      bool create(sp(::user::interaction) pwndParent, id id);

      virtual void install_message_handling(::ca::message::dispatch * pdispatch);

      virtual void _001OnDraw(::ca::graphics * pdc);
      void GetStepHoverRect(int32_t iStep, LPRECT lprect);
      void GetStepRect(int32_t iStep, LPRECT lprect);

      int32_t hit_test(point point);

      void UpdateHover();


      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)
   };

} // namespace user