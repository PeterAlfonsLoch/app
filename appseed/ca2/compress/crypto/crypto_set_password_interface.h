// ICoder.h
// from 7-zip
#pragma once

namespace crypto
{

   class CLASS_DECL_ca2 set_password_interface :
      virtual public ::ca2::object
   {
   public:
     virtual ::ca2::HRes CryptoSetPassword(const byte *data, uint32_t size) = 0;
   };

} // namespace crypto