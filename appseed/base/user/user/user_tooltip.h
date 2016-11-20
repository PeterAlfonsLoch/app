#pragma once


namespace user
{


   class CLASS_DECL_BASE tooltip:
      virtual public ::user::interaction
   {
   public:


      string               m_str;
      ::draw2d::font_sp    m_font;
      ::size               m_size;
      bool                 m_bError;


      tooltip(::aura::application * papp);
      virtual ~tooltip();

#ifdef DEBUG
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
#endif

      void install_message_handling(::message::dispatch * pinterface) override;

      ::size CalcSize();

      DECL_GEN_SIGNAL(_001OnCreate);
      void _001OnTimer(::timer * ptimer) override;
      void _001OnDraw(::draw2d::graphics * pgraphics) override;


      bool get_translucency(::user::ETranslucency  & etranslucency) override;


      virtual ::user::interaction::e_type get_window_type() override;


   };


} // namespace veritile







