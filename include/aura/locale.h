#pragma once

#if defined(ANDROID)
#define index system_index
#define lconv system_lconv
#define localeconv system_localeconv
#endif //ANDROID


#include <locale.h>


#if defined(ANDROID)
#undef index system_index
#undef lconv system_lconv
#undef localeconv system_localeconv
#endif //ANDROID