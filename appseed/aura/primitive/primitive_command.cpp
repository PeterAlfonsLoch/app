//#include "framework.h"


namespace primitive
{


   command::command(::aura::application * papp) :
      object(papp)
   {

      m_ecommand = command_default;

   }

   command::command(::aura::application * papp, e_command ecommand) :
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


   void command::on_request(::create * pcreate)
   {

      UNREFERENCED_PARAMETER(pcreate);

   }


   string command::get_description()
   {

      return "this is a command that was not described";

   }


} // namespace primitive