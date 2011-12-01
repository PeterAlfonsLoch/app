#include "StdAfx.h"


namespace gen
{


   command::command(::ca::application * papp) :
      ca(papp)
   {
   }

   command::~command()
   {
   }


   var command::run()
   {
      return true;
   }

   void command::on_request(::ca::create_context * pcreatecontext)
   {
      UNREFERENCED_PARAMETER(pcreatecontext);
   }

   string command::get_description()
   {
      return "this is a command that was not described";
   }

} // namespace command