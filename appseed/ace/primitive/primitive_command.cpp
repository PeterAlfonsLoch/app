//#include "framework.h"


namespace primitive
{


   command::command(::ace::application * papp) :
      object(papp)
   {

      m_ecommand = command_default;

   }

   command::command(::ace::application * papp, e_command ecommand) :
      object(papp)
   {

      m_ecommand = ecommand;

   }

   command::~command()
   {

   }


   var command::run()
   {

      return true;

   }


   void command::on_request(sp(::create) pcreatecontext)
   {

      UNREFERENCED_PARAMETER(pcreatecontext);

   }


   string command::get_description()
   {

      return "this is a command that was not described";

   }


} // namespace primitive