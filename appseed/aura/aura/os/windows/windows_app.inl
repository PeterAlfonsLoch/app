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

int32_t WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   return node_main(hinstance, hPrevInstance, lpCmdLine, nCmdShow);

}

END_EXTERN_C

