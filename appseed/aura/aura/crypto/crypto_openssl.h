#pragma once


#include <openssl/md5.h>
#include <openssl/whrlpool.h>


template < >
CLASS_DECL_AURA void to_string(string & str, const MD5_CTX & ctx);

template < >
CLASS_DECL_AURA void to_string(string & str, const WHIRLPOOL_CTX & ctx);


