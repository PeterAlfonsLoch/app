


app_install_launcher::app_install_launcher(const char * pszVersion,const char * pszBuild)
{

   m_strVersion   = pszVersion;

   m_strBuild     = pszBuild;

   m_bPrivileged = true;

}


bool app_install_launcher::ensure_executable()
{

   m_strPath = path::app_install();

   return true;

}

string app_install_launcher::get_executable_path()
{
   ensure_executable();
   return m_strPath;
}


