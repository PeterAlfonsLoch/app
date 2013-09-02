#pragma once


namespace user
{


   class CLASS_DECL_ca2 edit_plain_text_view :
      virtual public view,
      public edit_plain_text
   {
   public:

      
      
      edit_plain_text_view(sp(::application) papp);

      virtual void install_message_handling(::ca2::message::dispatch * pinterface);

      virtual void _001OnSetText();
      virtual void _001OnUpdate();

      virtual void layout();


   };


} // namespace user


