#pragma once

namespace user
{


   class CLASS_DECL_CORE step_slider :
      public ::user::interaction
   {
   public:


      int_scalar              m_scalar;

      bool                    m_bHover;
      int64_t                 m_iHover;
      int64_t                 m_iLButtonDown;


      step_slider(sp(::aura::application) papp);
      virtual ~step_slider();

      bool create_window(const RECT & rect, sp(::user::interaction) pwndParent, id id);

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      void GetStepHoverRect(LPRECT lprect, int64_t iVal, int64_t iMin, int64_t iMax, LPCRECT lpcrectClient);
      void GetStepRect(LPRECT lprect, int64_t iVal, int64_t iMin, int64_t iMax, LPCRECT lpcrectClient);

      int64_t hit_test(point point);

      void UpdateHover();


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
   };

} // namespace user