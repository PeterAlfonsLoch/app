#pragma once

class CLASS_DECL_CA2_CUBE netnodeLibraryClass :
   virtual public ::radix::object
{
public:
   netnodeLibraryClass(::ca::application * papp);
   ~netnodeLibraryClass(void);

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


   netnodeScriptManager * m_pmanager;


   ::ca::application * get_app() const;

};
