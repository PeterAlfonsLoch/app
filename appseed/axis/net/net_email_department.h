#pragma once


namespace net
{


   class CLASS_DECL_AXIS email_department :
      virtual public ::aura::department
   {
   public:


      email_department(::aura::application * papp);


      bool utf8_mail(class ::net::email & email);


      bool syntax_is_valid(const char * pszCandidate);


   };


} // namespace net





