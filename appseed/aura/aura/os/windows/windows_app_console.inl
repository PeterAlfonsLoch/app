#include "aura/aura/aura/aura.h"
#include "aura/aura/os/windows/windows.h"


#ifdef _WIN32
extern "C"
{
#undef APPMACROS_ONLY
#include <openssl/ms/applink.c>
}
#endif

BEGIN_EXTERN_C

int main(int argc, char *argv[])
{
   
   return ::node_main(argc, argv);
   
}

END_EXTERN_C

