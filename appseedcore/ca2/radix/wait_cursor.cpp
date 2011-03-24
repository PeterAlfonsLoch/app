#include "StdAfx.h"

wait_cursor::wait_cursor(::ca::application * papp) :
   ca(papp)
   { System.BeginWaitCursor(); }
 wait_cursor::~wait_cursor()
{
   AFX_BEGIN_DESTRUCTOR

   System.EndWaitCursor();

   AFX_END_DESTRUCTOR
}
 void wait_cursor::Restore()
   { System.RestoreWaitCursor(); }


 