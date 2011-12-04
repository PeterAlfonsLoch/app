#pragma once

namespace userbase
{

   class CLASS_DECL_ca2 button :
      virtual public user::button
   {
   public:

      visual::dib_sp          m_dib;

      button(::ca::application * papp);
   public:
      virtual ~button();

      virtual void ResizeToFit();

      virtual ::ca::font * _001GetFont(void);

      virtual void install_message_handling(::gen::message::dispatch * pinterface);

      virtual void _001OnDraw(::ca::graphics * pdc);

      DECL_GEN_SIGNAL(_001OnCreate)

   };

} // namespace userbase