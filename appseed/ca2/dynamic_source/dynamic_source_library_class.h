#pragma once

namespace dynamic_source
{

   class CLASS_DECL_ca library_class :
      virtual public ::radix::object
   {
   public:
      library_class(::ca::application * papp);
      ~library_class(void);

      http::memory_file m_memfileError;
      string m_strName;
      stringa m_straSourcePath;
      stringa m_straCppPath;
      string m_strLibraryPath;
      HMODULE m_hmodule;
      base_array < FILETIME, FILETIME & > m_ftaCreation;
      base_array < FILETIME, FILETIME & > m_ftaAccess;
      base_array < FILETIME, FILETIME & > m_ftaModified;




      bool DoesMatchVersion();
      void Load();
      void Unload();


      script_manager * m_pmanager;


      ::ca::application * get_app() const;

   };


} // namespace dynamic_source


