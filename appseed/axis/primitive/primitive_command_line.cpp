#include "framework.h"


command_line::command_line(sp(::axis::application) papp) :
   element(papp),
   m_eventReady(papp)
{
   common_construct();
}

void command_line::common_construct()
{
   m_bShowSplash     = TRUE;
   m_bRunEmbedded    = FALSE;
   m_bRunAutomated   = FALSE;
   m_ecommand        = command_file_new;
   m_iEdge           = 0;
   m_puiParent       = NULL;
   m_pbiasCreate     = NULL;
}

command_line::~command_line()
{
}

void command_line::ParseParam(const char* pszParam, bool bFlag, bool bLast)
{
   if (bFlag)
      ParseParamFlag(pszParam);
   else
      ParseParamNotFlag(pszParam);

   ParseLast(bLast);
}

void command_line::ParseParamFlag(const char* pszParam)
{
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if(stricmp_dup(pszParam, "pt") == 0)
      m_ecommand = command_file_print_to;
   else if (stricmp_dup(pszParam, "p") == 0)
      m_ecommand = command_file_print;
   else if (stricmp_dup(pszParam, "Unregister") == 0 ||
      stricmp_dup(pszParam, "Unregserver") == 0)
      m_ecommand = command_app_unregister;
   else if (stricmp_dup(pszParam, "dde") == 0)
   {
      m_ecommand = command_file_dde;
   }
   else if (stricmp_dup(pszParam, "Embedding") == 0)
   {
      m_bRunEmbedded = TRUE;
      m_bShowSplash = FALSE;
   }
   else if (stricmp_dup(pszParam, "Automation") == 0)
   {
      m_bRunAutomated = TRUE;
      m_bShowSplash = FALSE;
   }
}

void command_line::ParseParamNotFlag(const char* pszParam)
{
   if (m_varFile.is_empty())
      m_varFile = pszParam;
   else if (m_ecommand == command_file_print_to && m_strPrinterName.is_empty())
      m_varFile = pszParam;
   else if (m_ecommand == command_file_print_to && m_strDriverName.is_empty())
      m_varFile = pszParam;
   else if (m_ecommand == command_file_print_to && m_strPortName.is_empty())
      m_varFile = pszParam;
}

void command_line::ParseLast(bool bLast)
{
   if (bLast)
   {
      if (m_ecommand == command_file_new && !m_varFile.is_empty())
         m_ecommand = command_file_open;
      m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
   }
}

command_line & command_line::operator = (const command_line & info)
{

   m_bShowSplash     = info.m_bShowSplash;
   m_bRunEmbedded    = info.m_bRunEmbedded;
   m_bRunAutomated   = info.m_bRunAutomated;
   m_varFile         = info.m_varFile;
   m_strPrinterName  = info.m_strPrinterName;
   m_strPortName     = info.m_strPortName;

   return *this;

}

void command_line::_001ParseCommandLine(const char * pszCommandLine)
{
   m_varQuery.propset()._008ParseCommandLine(pszCommandLine, m_varFile);
   if(!m_varFile.is_empty())
   {
      m_ecommand = command_line::command_file_open;
   }
   if(m_varQuery.has_property("uri"))
   {
      if(m_varFile.has_char())
      {
         m_varFile += ";";
         m_varFile += m_varQuery["uri"];
      }
      else
      {
         m_varFile = m_varQuery["uri"];
      }
      if(m_ecommand == command_line::command_file_new)
         m_ecommand = command_line::command_file_open;
   }
   if(m_ecommand == command_line::command_file_open)
   {
      m_varQuery["show_platform"] = 1;
   }

   if(m_varQuery.propset().has_property("app"))
   {
      m_strApp = m_varQuery.propset()["app"];
   }

   if(m_strApp == "session" && m_varQuery.propset().has_property("session_start"))
   {
      m_strApp = m_varQuery.propset()["session_start"];
   }

   if(m_varQuery.propset().has_property("app_type"))
   {
      m_strAppType = m_varQuery.propset()["app_type"];
   }

   if (!m_varQuery.propset().has_property("build_number")
      || m_varQuery["build_number"].is_empty())
   {

      if (file_exists_dup("C:\\ca2\\config\\plugin\\build_number.txt"))
      {

         string str = file_as_string_dup("C:\\ca2\\config\\plugin\\build_number.txt");

         m_varQuery["build_number"] = str;

      }

   }

}


void command_line::_001ParseCommandLineUri(const char * pszCommandLine)
{

   throw not_implemented(get_app());

}

void command_line::_001ParseCommandFork(const char * pszCommandFork)
{

   m_varQuery.propset()._008ParseCommandFork(pszCommandFork, m_varFile, m_strApp);
   if(!m_varFile.is_empty())
   {
      m_ecommand = command_line::command_file_open;
   }
   if(m_varQuery.has_property("uri"))
   {
      if(m_varFile.has_char())
      {
         m_varFile += ";";
         m_varFile += m_varQuery["uri"];
      }
      else
      {
         m_varFile = m_varQuery["uri"];
      }
      if(m_ecommand == command_line::command_file_new)
         m_ecommand = command_line::command_file_open;
   }
   if(m_ecommand == command_line::command_file_open)
   {
      m_varQuery["show_platform"] = 1;
   }

   if(m_varQuery.propset().has_property("app"))
   {
      m_strApp = m_varQuery.propset()["app"];
   }

   if(m_strApp == "session" && m_varQuery.propset().has_property("session_start"))
   {
      m_strApp = m_varQuery.propset()["session_start"];
   }

   if(m_varQuery.propset().has_property("app_type"))
   {
      m_strAppType = m_varQuery.propset()["app_type"];
   }

   //      m_pthreadParent->consolidate(this);

}



void command_line::_001ParseCommandForkUri(const char * pszCommandFork)
{

   throw not_implemented(get_app());

}



command_line_sp::command_line_sp()
{
}


command_line_sp::command_line_sp(allocatorsp allocer) :
   smart_pointer < command_line > (allocer)
{
}


