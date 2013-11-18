#pragma once


#include "crypto_sha1.h"
#include "crypto_nessie.h"
#include "crypto_hmac_sha1.h"


#include "crypto_crypto.h"




CLASS_DECL_BASE bool hex_to_memory(primitive::memory & memory, const char * pszHex);
CLASS_DECL_BASE void memory_to_hex(string & strHex, primitive::memory & memory);




