#include "framework.h"


namespace ca2
{


   command::command(sp(::ca2::application) papp) :
      ca2(papp)
   {
   }

   command::~command()
   {
   }


   var command::run()
   {
      return true;
   }

   void command::on_request(sp(::ca2::create_context) pcreatecontext)
   {
      UNREFERENCED_PARAMETER(pcreatecontext);
   }

   string command::get_description()
   {
      return "this is a command that was not described";
   }

} // namespace command