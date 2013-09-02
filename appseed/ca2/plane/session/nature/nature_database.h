#pragma once

class db_file_set;

namespace nature
{


   class CLASS_DECL_ca2 database :
      virtual public object
   {
   public:
      database(sp(::application) papp);
      virtual ~database();

      bool                    m_bInitialized;
      simpledb::file_set *           m_pimagefileset;
      void Finalize();
      bool Initialize();
      simpledb::file_set * GetImageFileSet();
      void UpdateImagePaths();

   };

} // namespace mplite