//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


wait_cursor::wait_cursor(::aura::application * papp) :
   ::object(papp)
{
	
	Application.BeginWaitCursor();

}


 wait_cursor::~wait_cursor()
{

    Application.EndWaitCursor();

}


void wait_cursor::Restore()
{
	
	Application.RestoreWaitCursor();

}


