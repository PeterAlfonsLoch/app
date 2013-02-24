#include "framework.h"


namespace gen
{

   void request_interface::create(::ca::create_context * pcreatecontext)
   {
      if(pcreatecontext->m_spCommandLine->m_varQuery["client_only"] != 0)
      {
         pcreatecontext->m_bClientOnly = true;
      }

      request(pcreatecontext);
   }

   void request_interface::add_line(const char * pszCommandLine, ::ca::application_bias * pbiasCreate)
   {
      gen::command_thread & commandcentral = get_app()->cast_app < ::gen::application > ().command_central();
      ::ca::create_context_sp createcontext(&commandcentral);
      createcontext->m_spApplicationBias = pbiasCreate;
      createcontext->m_spCommandLine->_001ParseCommandLine(pszCommandLine);
      commandcentral.consolidate(createcontext);
      System.command().consolidate(createcontext);
      create(createcontext);
   }

   void request_interface::add_line_uri(const char * pszCommandLine, ::ca::application_bias * pbiasCreate)
   {
      gen::command_thread & commandcentral = get_app()->cast_app < ::gen::application > ().command_central();
      ::ca::create_context_sp createcontext(&commandcentral);
      createcontext->m_spApplicationBias = pbiasCreate;
      createcontext->m_spCommandLine->_001ParseCommandLineUri(pszCommandLine);
      commandcentral.consolidate(createcontext);
      System.command().consolidate(createcontext);
      create(createcontext);
   }

   void request_interface::add_fork(const char * pszCommandFork, ::ca::application_bias * pbiasCreate)
   {
      gen::command_thread & commandcentral = get_app()->cast_app < ::gen::application > ().command_central();
      ::ca::create_context_sp createcontext(&commandcentral);
      createcontext->m_spApplicationBias = pbiasCreate;
      createcontext->m_spCommandLine->_001ParseCommandFork(pszCommandFork);
      commandcentral.consolidate(createcontext);
      System.command().consolidate(createcontext);
      create(createcontext);
   }

   void request_interface::add_fork_uri(const char * pszCommandFork, ::ca::application_bias * pbiasCreate)
   {
      gen::command_thread & commandcentral = get_app()->cast_app < ::gen::application > ().command_central();
      ::ca::create_context_sp createcontext(&commandcentral);
      createcontext->m_spApplicationBias = pbiasCreate;
      createcontext->m_spCommandLine->_001ParseCommandForkUri(pszCommandFork);
      commandcentral.consolidate(createcontext);
      System.command().consolidate(createcontext);
      create(createcontext);
   }

   void request_interface::request(var & varFile)
   {

      ::ca::create_context_sp createcontext(&get_app()->cast_app < ::gen::application > ().command());

      createcontext->m_spCommandLine->m_varFile              = varFile;

      request(createcontext);

      varFile = createcontext->m_spCommandLine->m_varFile;

   }

   void request_interface::request(var & varFile, var & varQuery)
   {

      ::ca::create_context_sp createcontext(&get_app()->cast_app < ::gen::application > ().command());

      createcontext->m_spCommandLine->m_varFile              = varFile;
      createcontext->m_spCommandLine->m_varQuery             = varQuery;
      if(!varFile.is_empty())
      {
         createcontext->m_spCommandLine->m_ecommand = ::gen::command_line::command_file_open;
      }

      request(createcontext);

      varFile                       = createcontext->m_spCommandLine->m_varFile;
      varQuery                      = createcontext->m_spCommandLine->m_varQuery;

   }

   void request_interface::request(gen::command_line * pcommandline)
   {

      ::ca::create_context_sp createcontext(get_app());

      createcontext->m_spCommandLine = pcommandline;

      on_request(createcontext);

   }

   void request_interface::request(::ca::create_context * pcreatecontext)
   {
      on_request(pcreatecontext);
   }

   void request_interface::on_request(::ca::create_context * pcreatecontext)
   {
      UNREFERENCED_PARAMETER(pcreatecontext);
   }


} // namespace gen

