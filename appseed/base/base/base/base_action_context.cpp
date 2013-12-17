#include "framework.h"


namespace action
{

   e_source translation_source(e_source esource, e_context econtextDst, e_context econtextSrc)
   {


      switch(econtextSrc)
      {
      case context_this_set_text:
         switch (econtextDst)
         {
         case context_this_on_after_change_text:
            return context_this_set_text;
         default:
            break:
         }
      default:
         break;
      }

      return esource;

   }



} // namespace action





