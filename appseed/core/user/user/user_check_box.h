#pragma once


namespace user
{


   class CLASS_DECL_CORE check_box :
      virtual public control,
      virtual public elemental
   {
   public:
      enum e_style
      {

         style_normal,
         style_red_green_circle,

      };
   protected:
      check::e_check    m_echeck;
      bool  m_bMouseDown;


   public:

      e_style     m_estyle;

      check_box(::aura::application * papp);
      virtual ~check_box();


   public:
      virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      virtual void _001OnDrawNormal(::draw2d::graphics * pgraphics);
      virtual void _001OnDrawRedGreenCircle(::draw2d::graphics * pgraphics);
      virtual check::e_check _001GetCheck();
      virtual void _001SetCheck(check::e_check check, ::action::context actioncontext);

      void install_message_handling(::message::dispatch * pinterface);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      void _001OnTimer(::timer * ptimer);

   };

} // namespace user