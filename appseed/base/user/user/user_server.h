#pragma once


namespace user
{


   class CLASS_DECL_BASE server :
      virtual public ::object
   {
   public:


      virtual ::user::document * open_new_document();
      virtual ::user::document * open_document_file(var varFile = ::var(), bool bMakeVisible = true, ::user::interaction * puiParent = NULL);
      virtual void on_request(::create * pcreate);


   };


} // namespace user




