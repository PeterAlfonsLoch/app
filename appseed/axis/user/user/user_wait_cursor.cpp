#include "framework.h"

wait_cursor::wait_cursor(sp(::axis::application) papp) :
   element(papp)
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


