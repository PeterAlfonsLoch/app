// IPassword.h


namespace crypto
{

   /*#ifndef __IPASSWORD_H
   #define __IPASSWORD_H

   #include "../Common/MyUnknown.h"
   #include "../Common/Types.h"

   #include "IDecl.h"

   #define PASSWORD_INTERFACE(i, x) DECL_INTERFACE(i, 5, x)*/

   class CLASS_DECL_ca get_text_password2_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes CryptoGetTextPassword2(int32_t *passwordIsDefined, string & password) = 0;
   };

} // namespace crypto
