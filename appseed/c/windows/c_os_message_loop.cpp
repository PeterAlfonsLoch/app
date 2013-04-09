#include "framework.h"


void _c_simple_message_loop()
{


   MSG msg;
	while(GetMessage(&msg, ::null(), 0, 0xffffffffu))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


}


