#pragma once


namespace user
{


   class CLASS_DECL_CORE form_view:
      virtual public ::user::scroll_view,
      virtual public ::user::form
   {
   public:


      form_view();
      virtual ~form_view();


      virtual void install_message_handling(::message::dispatch * pdispatch);

      void on_update(::aura::impact * pSender,LPARAM lHint,object* phint);

      virtual bool open_document(var varFile);

   };


} // namespace user

















































