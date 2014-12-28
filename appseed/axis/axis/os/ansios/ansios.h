#pragma once



CLASS_DECL_AXIS bool crypto_decrypt(::primitive::memory & storageDecrypt,const ::primitive::memory & storageEncrypt,const char * pszSalt);
CLASS_DECL_AXIS bool crypto_encrypt(::primitive::memory & storageEncrypt,const ::primitive::memory & storageDecrypt,const char * pszSalt);


