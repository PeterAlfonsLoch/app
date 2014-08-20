#pragma once


namespace net
{


   class CLASS_DECL_CORE email_departament :
      virtual public ::base::departament
   {
   public:


      email_departament(sp(::axis::application) papp);


      bool utf8_mail(class ::net::email & email);


      bool syntax_is_valid(const char * pszCandidate);


   };


} // namespace net





