#pragma once

namespace ca2
{

   class CLASS_DECL_ca2 compress :
      public ::ca2::object
   {
   public:


      bool ungz(sp(::ca2::application) papp, const char * lpcszUncompressed, const char * lpcszGzFileCompressed);
      bool gz(sp(::ca2::application) papp, const char * lpcszGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(::ca2::writer & ostreamUncompressed, const char * lpcszGzFileCompressed);
      bool gz(::ca2::writer & ostreamGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(::primitive::memory_file & memoryfile);

      bool unbz(sp(::ca2::application) papp, const char * lpcszUncompressed, const char * lpcszBzFileCompressed);
      bool bz(sp(::ca2::application) papp, const char * lpcszBzFileCompressed, const char * lpcszUncompressed);

      bool unbz(::ca2::writer & ostreamUncompressed, const char * lpcszBzFileCompressed);
      bool bz(::ca2::writer & ostreamBzFileCompressed, const char * lpcszUncompressed);

      bool bz_stream(::ca2::writer & ostreamBzFileCompressed, ::ca2::reader & istreamFileUncompressed);

      bool _compress(class primitive::memory & memory, void * pdata, ::primitive::memory_size ulSizeUncompressed);
      bool _uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, ::primitive::memory_size ulSizeUncompressed);


      bool null(::ca2::writer & ostream, ::ca2::reader & istream);


      void extract_all(const char * pszFile, sp(::ca2::application) papp);


      void zip(const char * pszZip, const char * psz, sp(::ca2::application) papp);
      void zip(const char * psz, sp(::ca2::application) papp);


      friend class application;


   };

} // namespace ca2



#ifdef WINDOWS
CLASS_DECL_ca2 int32_t my_open(const char * psz, int32_t i);
CLASS_DECL_ca2 FILE * my_fopen(const char * psz, const char * pszMode);
#else
CLASS_DECL_ca2 void _get_errno(int32_t * perrno);
CLASS_DECL_ca2 int32_t my_open(const char * psz, int32_t i);
CLASS_DECL_ca2 FILE * my_fopen(const char * psz, const char * pszMode);
#endif