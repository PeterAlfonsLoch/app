#include "framework.h"

#ifdef DEBUG

void DebugBaseEnum();

enum _vmsgenEDebugBaseEnum
{
   _vmsgenEDebugBaseEnumDefault,
   _vmsgenEDebugBaseEnum1
};
/*
class CVmsgenEDebugBaseEnum :
   public base_enum < _vmsgenEDebugBaseEnum, _vmsgenEDebugBaseEnumDefault>
{
   BASE_ENUM_DEFAULT_IN_DECLARE(CVmsgenEDebugBaseEnum, _vmsgenEDebugBaseEnum, _vmsgenEDebugBaseEnumDefault);
};
*/

void DebugBaseEnum()
{
   /*CVmsgenEDebugBaseEnum edebug;

   edebug = _vmsgenEDebugBaseEnum1;*/

}

#endif