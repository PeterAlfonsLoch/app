#pragma once

namespace userbase
{


   class CLASS_DECL_ca step_slider :
      public ::user::interaction
   {
   public:


      int            m_iScalar;
      IntScalar *    m_pscalar;


   protected:
      
      
      bool        m_bHover;
      int         m_iHover;
      int         m_iLButtonDown;


   public:
      step_slider(::ca::application * papp);
      virtual ~step_slider(void);

      bool create(::user::interaction * pwndParent, id id);

      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pdispatch);

      virtual void _001OnDraw(::ca::graphics * pdc);
      void GetStepHoverRect(int iStep, LPRECT lprect);
      void GetStepRect(int iStep, LPRECT lprect);

      int hit_test(point point);

      void UpdateHover();


      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)
   };

} // namespace userbase