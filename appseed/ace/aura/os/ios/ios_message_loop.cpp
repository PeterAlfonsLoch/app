#include "framework.h"


void _c_simple_message_loop()
{

   MESSAGE msg;
   
   while(GetMessageW(&msg, NULL, 0, 0))
	{
   
      TranslateMessage(&msg);
		
      DispatchMessage(&msg);
      
	}

}

