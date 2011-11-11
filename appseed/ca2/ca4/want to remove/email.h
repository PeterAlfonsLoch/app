#pragma once

namespace ca27
{


   class CLASS_DECL_ca2api00200002 email :
      virtual public base_object
   {
   public:
      email();

      bool utf8_mail(class ::email & email);

      bool syntax_is_valid(const char * pszCandidate);
   };

} // namespace ca27