#pragma once


class CLASS_DECL_AXIS app_install_launcher:
   virtual public ::launcher
{
public:

   string   m_strPath;
   string   m_strVersion;
   string   m_strBuild;
   string   m_strPlatform;

   app_install_launcher(const char * pszPlatform, const char * pszVersion,const char * pszBuild);

   virtual bool ensure_executable() override;

   virtual string get_executable_path() override;

   virtual void start_in_context(bool bAlreadyElevated);

};
