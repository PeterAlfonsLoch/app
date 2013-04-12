#pragma once

namespace ca
{


   class CLASS_DECL_ca2 email :
      virtual public ::ca::object
   {
   public:
      email();

      bool utf8_mail(class ::email & email);

      bool syntax_is_valid(const char * pszCandidate);
   };

} // namespace ca