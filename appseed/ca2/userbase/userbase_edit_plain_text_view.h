#pragma once

namespace userbase
{

   class CLASS_DECL_ca edit_plain_text_view :
      virtual public view,
      virtual public edit_plain_text
   {
   public:

      ::ax::font_sp m_font;

      edit_plain_text_view(::ax::application * papp);

      virtual void install_message_handling(::gen::message::dispatch * pinterface);

      virtual void _001OnSetText();
      virtual void _001OnUpdate();

      virtual void layout();
   };


} // namespace userbase