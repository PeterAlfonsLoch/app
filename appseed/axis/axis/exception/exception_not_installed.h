#pragma once


class CLASS_DECL_AXIS not_installed : 
   virtual public ::exception::base
{
public:


   string      m_strVersion;
   string      m_strBuild;
   string      m_strType;
   string      m_strId;
   string      m_strLocale;
   string      m_strSchema;


   not_installed(sp(::base::application) papp, const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema);
   not_installed(const not_installed & e);
   virtual ~not_installed();


};
