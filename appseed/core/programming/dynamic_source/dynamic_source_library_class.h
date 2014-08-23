#pragma once

/*
#include <sys/stat.h>


#if defined(APPLEOS) 


#if defined(_LP64)


#define stat64 stat


#endif


#endif
*/


namespace dynamic_source
{


   class CLASS_DECL_CORE library_class :
      virtual public ::object
   {
   public:


      file::memory_buffer                    m_memfileError;
      string                                 m_strName;
      stringa                                m_straSourcePath;
      stringa                                m_straCppPath;
      string                                 m_strLibraryPath;
      ::aura::library                        m_library;

      array < __time_t, __time_t & >         m_ftaCreation;
      array < __time_t, __time_t & >         m_ftaAccess;
      array < __time_t, __time_t & >         m_ftaModified;

      sp(script_manager)                     m_pmanager;



      library_class(sp(::aura::application) papp);
      ~library_class();





      bool DoesMatchVersion();
      void Load();
      void Unload();




     sp(::aura::application) get_app() const;

   };


} // namespace dynamic_source


