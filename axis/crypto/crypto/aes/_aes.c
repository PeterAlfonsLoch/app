 //O volume na unidade Z ‚ eco
 //O N£mero de S‚rie do Volume ‚ 4A91-94E4

 //Pasta de Z:\ca2\app\axis\crypto\crypto\aes

#if defined(OPENSSL_NO_ASM)
#include "aes_cbc.c"
#endif
#include "aes_cfb.c"
#ifdef __ARM_ARCH_7A__
#include "aes_core.c"
#endif
#include "aes_ctr.c"
#include "aes_ecb.c"
#include "aes_ige.c"
#if defined(_M_X64) || defined(_LP64)
#include "aes_misc.c"
#endif
#if defined(__APPLE__) && !defined(_LP64)
#include "aes_misc.c"
#endif
#include "aes_ofb.c"
#include "aes_wrap.c"
// - Hi, I am Cortisol!!
// - So let's reflect you !!
// G: Passcrypt (No Weblang...) : on a Terminal t (.i.e. type, and press enter): clang -arch arm -dM -E - < /dev/null 
#if !defined(_M_X64) && !defined(_LP64) && !defined(__ARM_ARCH)
//#error "I know how to issue an error too!"
//#include "aes_x86core.c"
#endif
//2015-02-03  04:55                 0 _aes.c"
//              11 arquivo(s)        136.139 bytes
//               0 pasta(s)   29.041.606.656 bytes dispon¡veis
