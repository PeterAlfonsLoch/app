#include "framework.h"


keep_bool::keep_bool(bool * pKept, bool keepValue, bool keepAwayValue, bool bStartKept) :
   keep < bool >(pKept, keepValue, keepAwayValue, bStartKept)
{


}


keep_bool::~keep_bool()
{

   KeepAway();

}
