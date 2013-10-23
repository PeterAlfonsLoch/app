// IPassword.h


namespace crypto
{

   /*#ifndef __IPASSWORD_H
   #define __IPASSWORD_H

   #include "../Common/MyUnknown.h"
   #include "../Common/Types.h"

   #include "IDecl.h"

   #define PASSWORD_INTERFACE(i, x) DECL_INTERFACE(i, 5, x)*/

   class CLASS_DECL_CORE get_text_password_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes CryptoGetTextPassword(string & str) = 0;
   };

} // namespace crypto
