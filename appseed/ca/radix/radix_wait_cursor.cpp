#include "framework.h"

wait_cursor::wait_cursor(::ca::application * papp) :
   ca(papp)
   { System.BeginWaitCursor(); }
 wait_cursor::~wait_cursor()
{
   //__BEGIN_DESTRUCTOR

   System.EndWaitCursor();

   //__END_DESTRUCTOR
}
 void wait_cursor::Restore()
   { System.RestoreWaitCursor(); }


 