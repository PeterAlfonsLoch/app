


install_launcher::install_launcher(const char * pszVersion,const char * pszBuild)
{

   m_strVersion   = pszVersion;

   m_strBuild     = pszBuild;

}


bool install_launcher::ensure_executable()
{

   string strPath;

   string strPlatform = "x86";

   wstring wstrPath = utf8_to_16((string("\\ca2\\install\\stage\\") + strPlatform + "\\app.install.exe").c_str());

   get_program_files_x86(wstrPath);

   strPath = utf16_to_8(wstrPath.c_str());

   m_strPath = strPath;

   return true;

}

string install_launcher::get_executable_path()
{
   ensure_executable();
   return m_strPath;
}

