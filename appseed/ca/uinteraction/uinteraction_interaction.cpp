#include "framework.h"


namespace uinteraction
{


   interaction::interaction(::ca::applicationsp papp) :
      ca(papp)
   {
   }
      
   
   interaction::~interaction()
   {
   }


   void interaction::update()
   {
   }

   void interaction::get_frame_schema_list(stringa & stra)
   {

      UNREFERENCED_PARAMETER(stra);

   }

   frame::frame * interaction::get_frame_schema(const char * pszSchema)
   {
      
      UNREFERENCED_PARAMETER(pszSchema);

      return ::null();

   }


} // namespace uinteraction



