#include "framework.h"


not_installed::not_installed(sp(::axis::application) papp, const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{
      string str;
   m_strVersion         = pszVersion;
   str += "version=" + m_strVersion + ";";
   m_strBuild           = pszBuild;
   str += "build=" + m_strBuild + ";";
   m_strType            = pszType;
   str += "type=" + m_strType + ";";
   m_strId              = pszId;
   str += "idn=" + m_strId + ";";
   m_strLocale          = pszLocale;
   str += "locale=" + m_strLocale + ";";
   m_strSchema          = pszSchema;
   str += "schema=" + m_strSchema + ";";
   printf(":not_installed(\"%s\")", str.c_str());

}

not_installed::not_installed(const not_installed & e) :
   element(e),
   ::call_stack(e),
   ::exception::base(e)
{
      printf(":not_installed(copy)");
   m_strVersion         = e.m_strVersion;
   m_strBuild           = e.m_strBuild;
   m_strType            = e.m_strType;
   m_strId              = e.m_strId;
   m_strLocale          = e.m_strLocale;
   m_strSchema          = e.m_strSchema;

}


not_installed::~not_installed()
{


}

