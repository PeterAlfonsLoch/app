#pragma once

namespace user
{

   class CLASS_DECL_CORE check_box :
      virtual public control,
      virtual public check_interface
   {
   public:
      check_box(sp(::axis::application) papp);
      virtual ~check_box();

   protected:
      check::e_check    m_echeck;
      bool  m_bMouseDown;

   public:
      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual check::e_check _001GetCheck();
      virtual void _001SetCheck(check::e_check check, ::action::context actioncontext);

      void install_message_handling(::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnTimer);

   };

} // namespace user