#include "framework.h"
#include "axis/user/user.h"


bool TranslateMessage(LPMESSAGE lpmessage)
{

   UNREFERENCED_PARAMETER(lpmessage);

   return true;

}


LRESULT DispatchMessage(LPMESSAGE lpmessage)
{

   if(lpmessage->hwnd == NULL)
      return false;

   return window_from_handle(lpmessage->hwnd)->message_handler(lpmessage);

}



void _c_simple_message_loop()
{

   MESSAGE msg;

	while(GetMessage(&msg, NULL, 0, 0))
	{

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}


}


