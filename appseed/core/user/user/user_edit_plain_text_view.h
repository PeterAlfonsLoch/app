#pragma once


namespace user
{


   class CLASS_DECL_CORE edit_plain_text_view :
      virtual public scroll_view,
      virtual public edit_plain_text
   {
   public:

      
      
      edit_plain_text_view(sp(::aura::application) papp);

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001OnSetText(::action::context actioncontext);
      virtual void _001OnUpdate(::action::context actioncontext);

      virtual void layout();

      virtual void walk_pre_translate_tree(signal_details * pobj,sp(::user::interaction) puiStop);

   };


} // namespace user


