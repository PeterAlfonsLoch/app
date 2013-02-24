#pragma once

namespace ca2
{

   class CLASS_DECL_ca compress :
      public ::gen::object
   {
   public:


      bool ungz(::ca::application * papp, const char * lpcszUncompressed, const char * lpcszGzFileCompressed);
      bool gz(::ca::application * papp, const char * lpcszGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(gen::writer & ostreamUncompressed, const char * lpcszGzFileCompressed);
      bool gz(gen::writer & ostreamGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(::primitive::memory_file & memoryfile);

      bool unbz(::ca::application * papp, const char * lpcszUncompressed, const char * lpcszBzFileCompressed);
      bool bz(::ca::application * papp, const char * lpcszBzFileCompressed, const char * lpcszUncompressed);

      bool unbz(gen::writer & ostreamUncompressed, const char * lpcszBzFileCompressed);
      bool bz(gen::writer & ostreamBzFileCompressed, const char * lpcszUncompressed);

      bool bz_stream(gen::writer & ostreamBzFileCompressed, gen::reader & istreamFileUncompressed);

      bool _compress(class primitive::memory & memory, void * pdata, ::primitive::memory_size ulSizeUncompressed);
      bool _uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, ::primitive::memory_size ulSizeUncompressed);


      bool null(gen::writer & ostream, gen::reader & istream);


      void extract_all(const char * pszFile, ::ca::application * papp);


      void zip(const char * pszZip, const char * psz, ::ca::application * papp);
      void zip(const char * psz, ::ca::application * papp);


      friend class application;


   };

} // namespace ca2



#ifdef WINDOWS
CLASS_DECL_ca int32_t my_open(const char * psz, int32_t i);
CLASS_DECL_ca FILE * my_fopen(const char * psz, const char * pszMode);
#else
CLASS_DECL_ca void _get_errno(int32_t * perrno);
CLASS_DECL_ca int32_t my_open(const char * psz, int32_t i);
CLASS_DECL_ca FILE * my_fopen(const char * psz, const char * pszMode);
#endif