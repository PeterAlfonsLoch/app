#pragma once

namespace dynamic_source
{

   class CLASS_DECL_ca library_class :
      virtual public ::radix::object
   {
   public:


      http::memory_file m_memfileError;
      string m_strName;
      stringa m_straSourcePath;
      stringa m_straCppPath;
      string m_strLibraryPath;
      ::ca::library m_library;
      base_array < FILETIME, FILETIME & > m_ftaCreation;
      base_array < FILETIME, FILETIME & > m_ftaAccess;
      base_array < FILETIME, FILETIME & > m_ftaModified;
      script_manager * m_pmanager;



      library_class(::ca::application * papp);
      ~library_class(void);





      bool DoesMatchVersion();
      void Load();
      void Unload();




      ::ca::application * get_app() const;

   };


} // namespace dynamic_source


