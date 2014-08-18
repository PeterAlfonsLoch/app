#include "framework.h"


static struct lconv g_lconv = { "." };

struct lconv * localeconv(void)
{
   return &g_lconv;
}
