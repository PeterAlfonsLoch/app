#pragma once


namespace install
{


   class CLASS_DECL_AXIS installer_launcher :
      virtual public ::launcher,
      virtual public ::object
   {
   public:

      string   m_strPath;
      string   m_strVersion;
      string   m_strBuild;


      installer_launcher(::aura::application * papp, const char * pszVersion, const char * pszBuild);

      virtual bool ensure_executable();

      virtual string get_executable_path();

   };


} // namespace install



