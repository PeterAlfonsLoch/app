#pragma once


class CLASS_DECL_AXIS app_install_launcher:
   virtual public ::launcher
{
public:

   string   m_strPath;
   string   m_strVersion;
   string   m_strBuild;


   app_install_launcher(const char * pszVersion,const char * pszBuild);

   virtual bool ensure_executable();

   virtual string get_executable_path();

   virtual void start_in_context();

};
