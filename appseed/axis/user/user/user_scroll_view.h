#pragma once


namespace user
{


   class scroll_bar;


   class CLASS_DECL_AXIS scroll_view:
      virtual public impact,
      virtual public scroll_control
   {
   public:


      scroll_view(sp(::aura::application) papp);
      virtual ~scroll_view();


      virtual void install_message_handling(::message::dispatch * pdispatch);


   };


} // namespace user







