#include "framework.h"
#include "metrowin.h"


void _c_simple_message_loop()
{

   MESSAGE msg;
	while(GetMessage(&msg, NULL, 0, 0xffffffffu))
	{
      throw "todo";
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
	}


}


