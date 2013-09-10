#include "framework.h"

wait_cursor::wait_cursor(sp(base_application) papp) :
   base_element(papp)
   { System.BeginWaitCursor(); }
 wait_cursor::~wait_cursor()
{
   //__BEGIN_DESTRUCTOR

   System.EndWaitCursor();

   //__END_DESTRUCTOR
}
 void wait_cursor::Restore()
   { System.RestoreWaitCursor(); }


