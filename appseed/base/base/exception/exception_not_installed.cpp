#include "framework.h"


not_installed::not_installed(sp(::base::application) papp, const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema) :
   element(papp),
   ::call_stack(papp),
   ::exception::base(papp)
{

   m_strVersion         = pszVersion;
   m_strBuild           = pszBuild;
   m_strType            = pszType;
   m_strId              = pszId;
   m_strLocale          = pszLocale;
   m_strSchema          = pszSchema;

}

not_installed::not_installed(const not_installed & e) :
   element(e),
   ::call_stack(e),
   ::exception::base(e)
{

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

