#pragma once


class CLASS_DECL_c not_installed : 
   virtual public ::exception::base
{
public:


   vsstring      m_strVersion;
   vsstring      m_strBuild;
   vsstring      m_strType;
   vsstring      m_strId;
   vsstring      m_strLocale;
   vsstring      m_strSchema;


   not_installed(sp(::application) papp, const char * pszVersion, const char * pszBuild, const char * pszType, const char * pszId, const char * pszLocale, const char * pszSchema);
   not_installed(const not_installed & e);
   virtual ~not_installed();


};
