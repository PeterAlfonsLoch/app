#pragma once


#ifdef cplusplus


int32_t crypto_encrypt(memory & storageEncrypt,const memory & storageDecrypt,memory & key);
int32_t crypto_decrypt(memory & storageDecrypt,const memory & storageEncrypt,memory & key);


#endif


#include "ansios_multithreading.h"
