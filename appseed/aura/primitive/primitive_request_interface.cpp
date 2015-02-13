//#include "framework.h"


//void object::create(sp(::create) pcreatecontext)
//{
//   if(pcreatecontext->m_spCommandLine->m_varQuery["client_only"] != 0)
//   {
//      pcreatecontext->m_bClientOnly = true;
//   }
//
//   request_create(pcreatecontext);
//}
//
//void ::object::add_line(const char * pszCommandLine, application_bias * pbiasCreate)
//{
//   ::command_thread * commandcentral = get_app()->command_central();
//   sp(::create) createcontext(canew(::create(commandcentral)));
//   createcontext->m_spApplicationBias = pbiasCreate;
//   createcontext->m_spCommandLine->_001ParseCommandLine(pszCommandLine);
//
//   if (get_app()->command_central()->m_varTopicQuery.has_property("appid"))
//   {
//
//      if (createcontext->m_spCommandLine->m_varQuery["app"].is_empty())
//      {
//
//         createcontext->m_spCommandLine->m_varQuery["app"] = get_app()->command_central()->m_varTopicQuery["appid"];
//
//      }
//      else
//      {
//
//         createcontext->m_spCommandLine->m_varQuery["app"].stra().insert_at(0, get_app()->command_central()->m_varTopicQuery["appid"].get_string());
//
//      }
//
//      createcontext->m_spCommandLine->m_strApp = createcontext->m_spCommandLine->m_varQuery["app"];
//
//   }
//
//   if (get_app()->command_central()->m_varTopicQuery["build_number"].has_char())
//   {
//
//      createcontext->m_spCommandLine->m_varQuery["build_number"] = get_app()->command_central()->m_varTopicQuery["build_number"];
//
//   }
//   else if (createcontext->m_spCommandLine->m_varQuery["build_number"].is_empty())
//   {
//
//      if(createcontext->m_spCommandLine->m_strApp.CompareNoCase("app-core/netnodelite") == 0)
//      {
//
//         createcontext->m_spCommandLine->m_varQuery["build_number"] = "static";
//
//      }
//      else
//      {
//
//         createcontext->m_spCommandLine->m_varQuery["build_number"] = "installed";
//
//      }
//
//   }
//
//   commandcentral->consolidate(createcontext);
//   System.command()->consolidate(createcontext);
//   create(createcontext);
//}
//
//void ::object::add_line_uri(const char * pszCommandLine, application_bias * pbiasCreate)
//{
//   sp(::command_thread) commandcentral = get_app()->command_central();
//   sp(::create) createcontext(canew(::create(commandcentral)));
//   createcontext->m_spApplicationBias = pbiasCreate;
//   createcontext->m_spCommandLine->_001ParseCommandLineUri(pszCommandLine);
//   commandcentral->consolidate(createcontext);
//   System.command()->consolidate(createcontext);
//   create(createcontext);
//}
//
//void ::object::add_fork(const char * pszCommandFork, application_bias * pbiasCreate)
//{
//   sp(::command_thread) commandcentral = get_app()->command_central();
//   sp(::create) createcontext(canew(::create(commandcentral)));
//   createcontext->m_spApplicationBias = pbiasCreate;
//   createcontext->m_spCommandLine->_001ParseCommandFork(pszCommandFork);
//   commandcentral->consolidate(createcontext);
//   System.command()->consolidate(createcontext);
//   create(createcontext);
//}
//
//void ::object::add_fork_uri(const char * pszCommandFork, application_bias * pbiasCreate)
//{
//   sp(::command_thread) commandcentral = get_app()->command_central();
//   sp(::create) createcontext(canew(::create(commandcentral)));
//   createcontext->m_spApplicationBias = pbiasCreate;
//   createcontext->m_spCommandLine->_001ParseCommandForkUri(pszCommandFork);
//   commandcentral->consolidate(createcontext);
//   System.command()->consolidate(createcontext);
//   create(createcontext);
//}
//
//void ::object::request_file(var & varFile)
//{
//
//   sp(::command_thread) commandcentral = get_app()->command_central();
//   sp(::create) createcontext(canew(::create(commandcentral)));
//
//   createcontext->m_spCommandLine->m_varFile              = varFile;
//
//   request_create(createcontext);
//
//   varFile = createcontext->m_spCommandLine->m_varFile;
//
//}
//
//void ::object::request_file_query(var & varFile, var & varQuery)
//{
//
//   sp(::command_thread) commandcentral = get_app()->command_central();
//   sp(::create) createcontext(canew(::create(commandcentral)));
//
//   createcontext->m_spCommandLine->m_varFile              = varFile;
//   createcontext->m_spCommandLine->m_varQuery             = varQuery;
//   if(!varFile.is_empty())
//   {
//      createcontext->m_spCommandLine->m_ecommand = command_line::command_file_open;
//   }
//
//   request_create(createcontext);
//
//   varFile                       = createcontext->m_spCommandLine->m_varFile;
//   varQuery                      = createcontext->m_spCommandLine->m_varQuery;
//
//}
//
//void ::object::request_command(sp(command_line) pcommandline)
//{
//
//   sp(::command_thread) commandcentral = get_app()->command_central();
//   sp(::create) createcontext(canew(::create(commandcentral)));
//
//   createcontext->m_spCommandLine = pcommandline;
//
//   request_create(createcontext);
//
//}
//
//void ::object::request_create(sp(::create) pcreatecontext)
//{
//   on_request(pcreatecontext);
//}
//
//void object::on_request(sp(::create) pcreatecontext)
//{
//   
//   UNREFERENCED_PARAMETER(pcreatecontext);
//
//}
//
//
