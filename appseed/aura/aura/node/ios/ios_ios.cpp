#include "framework.h"



___IOS_STATE gen_MacState;




/////////////////////////////////////////////////////////////////////////////
// export WinMain to force linkage to this module
extern int32_t CLASS_DECL_AURA __win_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow);





void CLASS_DECL_AURA __ios_term()
{

}



void CLASS_DECL_AURA __abort()
{
   __ios_term();
   abort();
}




#ifdef DEBUG
bool CLASS_DECL_AURA __check_memory()
{
   return false;
}
#endif




