#include "framework.h"






#ifdef DEBUG

namespace ___FlagsDebug
{
   
   
   void FlagsDebug();

   enum ___EFlagsDebug
   {
      ___FlagsDebugA,
      ___FlagsDebugB,
      ___FlagsDebugC,
      ___FlagsDebugD,
      ___FlagsDebugE,
   };
   void FlagsDebug()
   {
      flags < ___EFlagsDebug > flagsdebug;
      flagsdebug.signalize(___FlagsDebugA);
      flagsdebug.unsignalize(___FlagsDebugB);
      flags < ___EFlagsDebug > flagsdebugB;
      flagsdebugB = flagsdebug;
   
   
      flags < ___EFlagsDebug > flagsdebugC;
      flagsdebugC.signalize(___FlagsDebugA);
      flagsdebugC.signalize(___FlagsDebugB);
      flagsdebugC.signalize(___FlagsDebugC);
      flagsdebugC.signalize(___FlagsDebugD);
      ASSERT(flagsdebugC.is_signalized(___FlagsDebugA));
      ASSERT(flagsdebugC.is_signalized(___FlagsDebugB));
      ASSERT(flagsdebugC.is_signalized(___FlagsDebugD));
      ASSERT(flagsdebugC.is_signalized(___FlagsDebugD));
      ASSERT(!flagsdebugC.is_signalized(___FlagsDebugE));
      flagsdebugC.unsignalize(___FlagsDebugD);
      ASSERT(flagsdebugC.is_signalized(___FlagsDebugA));
      ASSERT(flagsdebugC.is_signalized(___FlagsDebugB));
      ASSERT(flagsdebugC.is_signalized(___FlagsDebugD));
      ASSERT(!flagsdebugC.is_signalized(___FlagsDebugD));
      ASSERT(!flagsdebugC.is_signalized(___FlagsDebugE));
   }

} // namespace ___FlagsDebug

#endif // DEBUG




void axis_sort_serializable_int_ptr_array::on_after_read()
{
   quick_sort();
}