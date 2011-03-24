#include "StdAfx.h"
#include <float.h>



/////////////////////////////////////////////////////////////////////////////
// Diagnostic Stream output for floating point numbers

#ifdef _DEBUG
dump_context& dump_context::operator<<(float f)
{
   char szBuffer[32];
   _template::checked::gcvt_s(szBuffer, 32, f, FLT_DIG);

   *this << szBuffer;
   return *this;
}

dump_context& dump_context::operator<<(double d)
{
   char szBuffer[32];
   _template::checked::gcvt_s(szBuffer, 32, d, DBL_DIG);

   *this << szBuffer;
   return *this;
}
#endif
