//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


wait_cursor::wait_cursor(::aura::application * papp) :
   ::object(papp)
   { Application.BeginWaitCursor(); }
 wait_cursor::~wait_cursor()
{
   //__BEGIN_DESTRUCTOR

    Application.EndWaitCursor();

   //__END_DESTRUCTOR
}
 void wait_cursor::Restore()
 {
    Application.RestoreWaitCursor();
 }


