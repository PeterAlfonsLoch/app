#pragma once


#ifdef cplusplus


int32_t crypto_encrypt(::primitive::memory & storageEncrypt,const ::primitive::memory & storageDecrypt,::primitive::memory & key);
int32_t crypto_decrypt(::primitive::memory & storageDecrypt,const ::primitive::memory & storageEncrypt,::primitive::memory & key);


#endif


#include "ansios_multithreading.h"
