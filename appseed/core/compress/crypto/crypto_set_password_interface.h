// ICoder.h
// from 7-zip
#pragma once

namespace crypto
{

   class CLASS_DECL_CORE set_password_interface :
      virtual public ::object
   {
   public:
     virtual HRes CryptoSetPassword(const byte *data, uint32_t size) = 0;
   };

} // namespace crypto
