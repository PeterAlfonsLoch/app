#pragma once

namespace ca
{

   class CLASS_DECL_ca compress :
      public ::ca::object
   {
   public:


      bool ungz(::ca::application * papp, const char * lpcszUncompressed, const char * lpcszGzFileCompressed);
      bool gz(::ca::application * papp, const char * lpcszGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(ca::writer & ostreamUncompressed, const char * lpcszGzFileCompressed);
      bool gz(ca::writer & ostreamGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(::primitive::memory_file & memoryfile);

      bool unbz(::ca::application * papp, const char * lpcszUncompressed, const char * lpcszBzFileCompressed);
      bool bz(::ca::application * papp, const char * lpcszBzFileCompressed, const char * lpcszUncompressed);

      bool unbz(ca::writer & ostreamUncompressed, const char * lpcszBzFileCompressed);
      bool bz(ca::writer & ostreamBzFileCompressed, const char * lpcszUncompressed);

      bool bz_stream(ca::writer & ostreamBzFileCompressed, ca::reader & istreamFileUncompressed);

      bool _compress(class primitive::memory & memory, void * pdata, ::primitive::memory_size ulSizeUncompressed);
      bool _uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, ::primitive::memory_size ulSizeUncompressed);


      bool null(ca::writer & ostream, ca::reader & istream);


      void extract_all(const char * pszFile, ::ca::application * papp);


      void zip(const char * pszZip, const char * psz, ::ca::application * papp);
      void zip(const char * psz, ::ca::application * papp);


      friend class application;


   };

} // namespace ca



#ifdef WINDOWS
CLASS_DECL_ca int32_t my_open(const char * psz, int32_t i);
CLASS_DECL_ca FILE * my_fopen(const char * psz, const char * pszMode);
#else
CLASS_DECL_ca void _get_errno(int32_t * perrno);
CLASS_DECL_ca int32_t my_open(const char * psz, int32_t i);
CLASS_DECL_ca FILE * my_fopen(const char * psz, const char * pszMode);
#endif