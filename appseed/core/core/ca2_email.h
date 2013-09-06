#pragma once

namespace ca2
{


   class CLASS_DECL_ca2 email :
      virtual public object
   {
   public:
      email();

      bool utf8_mail(class ::email & email);

      bool syntax_is_valid(const char * pszCandidate);
   };

} // namespace ca2
