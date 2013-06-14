#include "framework.h"


namespace ca2
{

   void request_interface::create(sp(::ca2::create_context) pcreatecontext)
   {
      if(pcreatecontext->m_spCommandLine->m_varQuery["client_only"] != 0)
      {
         pcreatecontext->m_bClientOnly = true;
      }

      request_create(pcreatecontext);
   }

   void request_interface::add_line(const char * pszCommandLine, ::ca2::application_bias * pbiasCreate)
   {
      sp(::ca2::command_thread) commandcentral = get_app()->cast_app < ::ca2::application > ().command_central();
      sp(::ca2::create_context) createcontext(canew(::ca2::create_context(commandcentral)));
      createcontext->m_spApplicationBias = pbiasCreate;
      createcontext->m_spCommandLine->_001ParseCommandLine(pszCommandLine);
      commandcentral->consolidate(createcontext);
      System.command()->consolidate(createcontext);
      create(createcontext);
   }

   void request_interface::add_line_uri(const char * pszCommandLine, ::ca2::application_bias * pbiasCreate)
   {
      sp(::ca2::command_thread) commandcentral = get_app()->cast_app < ::ca2::application > ().command_central();
      sp(::ca2::create_context) createcontext(canew(::ca2::create_context(commandcentral)));
      createcontext->m_spApplicationBias = pbiasCreate;
      createcontext->m_spCommandLine->_001ParseCommandLineUri(pszCommandLine);
      commandcentral->consolidate(createcontext);
      System.command()->consolidate(createcontext);
      create(createcontext);
   }

   void request_interface::add_fork(const char * pszCommandFork, ::ca2::application_bias * pbiasCreate)
   {
      sp(::ca2::command_thread) commandcentral = get_app()->cast_app < ::ca2::application > ().command_central();
      sp(::ca2::create_context) createcontext(canew(::ca2::create_context(commandcentral)));
      createcontext->m_spApplicationBias = pbiasCreate;
      createcontext->m_spCommandLine->_001ParseCommandFork(pszCommandFork);
      commandcentral->consolidate(createcontext);
      System.command()->consolidate(createcontext);
      create(createcontext);
   }

   void request_interface::add_fork_uri(const char * pszCommandFork, ::ca2::application_bias * pbiasCreate)
   {
      sp(::ca2::command_thread) commandcentral = get_app()->cast_app < ::ca2::application > ().command_central();
      sp(::ca2::create_context) createcontext(canew(::ca2::create_context(commandcentral)));
      createcontext->m_spApplicationBias = pbiasCreate;
      createcontext->m_spCommandLine->_001ParseCommandForkUri(pszCommandFork);
      commandcentral->consolidate(createcontext);
      System.command()->consolidate(createcontext);
      create(createcontext);
   }

   void request_interface::request_file(var & varFile)
   {

      sp(::ca2::command_thread) commandcentral = get_app()->cast_app < ::ca2::application > ().command_central();
      sp(::ca2::create_context) createcontext(canew(::ca2::create_context(commandcentral)));

      createcontext->m_spCommandLine->m_varFile              = varFile;

      request_create(createcontext);

      varFile = createcontext->m_spCommandLine->m_varFile;

   }

   void request_interface::request_file_query(var & varFile, var & varQuery)
   {

      sp(::ca2::command_thread) commandcentral = get_app()->cast_app < ::ca2::application > ().command_central();
      sp(::ca2::create_context) createcontext(canew(::ca2::create_context(commandcentral)));

      createcontext->m_spCommandLine->m_varFile              = varFile;
      createcontext->m_spCommandLine->m_varQuery             = varQuery;
      if(!varFile.is_empty())
      {
         createcontext->m_spCommandLine->m_ecommand = ::ca2::command_line::command_file_open;
      }

      request_create(createcontext);

      varFile                       = createcontext->m_spCommandLine->m_varFile;
      varQuery                      = createcontext->m_spCommandLine->m_varQuery;

   }

   void request_interface::request_command(sp(::ca2::command_line) pcommandline)
   {

      sp(::ca2::command_thread) commandcentral = get_app()->cast_app < ::ca2::application > ().command_central();
      sp(::ca2::create_context) createcontext(canew(::ca2::create_context(commandcentral)));

      createcontext->m_spCommandLine = pcommandline;

      request_create(createcontext);

   }

   void request_interface::request_create(sp(::ca2::create_context) pcreatecontext)
   {
      on_request(pcreatecontext);
   }

   void request_interface::on_request(sp(::ca2::create_context) pcreatecontext)
   {
      UNREFERENCED_PARAMETER(pcreatecontext);
   }


} // namespace ca2

