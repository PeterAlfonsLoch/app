#pragma once

namespace ca4
{

   class CLASS_DECL_ca compress :
      public ::radix::object
   {
   public:


      bool ungz(::ca::application * papp, const char * lpcszUncompressed, const char * lpcszGzFileCompressed);
      bool gz(::ca::application * papp, const char * lpcszGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(ex1::writer & ostreamUncompressed, const char * lpcszGzFileCompressed);
      bool gz(ex1::writer & ostreamGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(::gen::memory_file & memoryfile);

      bool unbz(::ca::application * papp, const char * lpcszUncompressed, const char * lpcszBzFileCompressed);
      bool bz(::ca::application * papp, const char * lpcszBzFileCompressed, const char * lpcszUncompressed);

      bool unbz(ex1::writer & ostreamUncompressed, const char * lpcszBzFileCompressed);
      bool bz(ex1::writer & ostreamBzFileCompressed, const char * lpcszUncompressed);

      bool bz_stream(ex1::writer & ostreamBzFileCompressed, ex1::reader & istreamFileUncompressed);

      bool _compress(class primitive::memory & memory, void * pdata, ::primitive::memory_size ulSizeUncompressed);
      bool _uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, ::primitive::memory_size ulSizeUncompressed);


      bool null(ex1::writer & ostream, ex1::reader & istream);


      void extract_all(const char * pszFile, ::ca::application * papp);


      void zip(const char * pszZip, const char * psz, ::ca::application * papp);
      void zip(const char * psz, ::ca::application * papp);


      friend class application;


   };

} // namespace ca4



#ifdef WINDOWS
CLASS_DECL_ca int my_open(const char * psz, int i);
CLASS_DECL_ca FILE * my_fopen(const char * psz, const char * pszMode);
#else
CLASS_DECL_ca void _get_errno(int * perrno);
CLASS_DECL_ca int my_open(const char * psz, int i);
CLASS_DECL_ca FILE * my_fopen(const char * psz, const char * pszMode);
#endif