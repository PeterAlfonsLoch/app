#include "syllomatterconsole/StdAfx.h"
#include "include/syllomatterconsole.h"

int _tmain(int argc, _TCHAR* argv[])
{
   syllomatter_console console;

   
   if(console.InitInstance())
   {
      console.Run();
      console.ExitInstance();
   }

	return 0;
}

