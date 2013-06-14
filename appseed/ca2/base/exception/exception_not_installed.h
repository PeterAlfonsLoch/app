#pragma once


class CLASS_DECL_ca2 not_installed : 
   virtual public base_exception
{
public:


   vsstring      m_strVersion;
   vsstring      m_strBuild;
   vsstring      m_strType;
   vsstring      m_strId;
   vsstring      m_strLocale;
   vsstring      m_strSchema;


   not_installed(sp(::ca2::application) papp, const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema);
   not_installed(const not_installed & e);
   virtual ~not_installed();


};
