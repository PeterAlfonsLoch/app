#include "framework.h"

wait_cursor::wait_cursor(sp(::application) papp) :
   element(papp)
   { System.BeginWaitCursor(); }
 wait_cursor::~wait_cursor()
{
   //__BEGIN_DESTRUCTOR

   System.EndWaitCursor();

   //__END_DESTRUCTOR
}
 void wait_cursor::Restore()
   { System.RestoreWaitCursor(); }


 