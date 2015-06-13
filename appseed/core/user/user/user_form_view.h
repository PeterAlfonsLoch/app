#pragma once


namespace user
{


   class CLASS_DECL_CORE form_view:
      virtual public ::user::show < ::user::form >
   {
   public:


      form_view();
      virtual ~form_view();


      void on_update(::user::impact * pSender,LPARAM lHint,object* phint);

      virtual bool open_document(var varFile);

   };


} // namespace user

















































