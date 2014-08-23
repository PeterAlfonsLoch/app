#pragma once


namespace base
{


   class CLASS_DECL_BASE compress :
      public object
   {
   public:


      bool ungz(sp(::aura::application) papp, const char * lpcszUncompressed, const char * lpcszGzFileCompressed);
      bool gz(sp(::aura::application) papp, const char * lpcszGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(::file::output_stream & ostreamUncompressed, const char * lpcszGzFileCompressed);
      bool gz(::file::output_stream & ostreamGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(::file::memory_buffer & memoryfile);

      bool unbz(sp(::aura::application) papp, const char * lpcszUncompressed, const char * lpcszBzFileCompressed);
      bool bz(sp(::aura::application) papp, const char * lpcszBzFileCompressed, const char * lpcszUncompressed);

      bool unbz(::file::output_stream & ostreamUncompressed, const char * lpcszBzFileCompressed);
      bool bz(::file::output_stream & ostreamBzFileCompressed, const char * lpcszUncompressed);

      bool bz_stream(::file::output_stream & ostreamBzFileCompressed, ::file::input_stream & istreamFileUncompressed);

      bool _compress(class primitive::memory & memory, void * pdata, ::primitive::memory_size ulSizeUncompressed);
      bool _uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, ::primitive::memory_size ulSizeUncompressed);

      bool null(::file::output_stream & ostream, ::file::input_stream & istream);

      void extract_all(const char * pszFile, sp(::aura::application) papp);

      void zip(const char * pszZip, const char * psz, sp(::aura::application) papp);
      void zip(const char * psz, sp(::aura::application) papp);


   };


} // namespace base



#ifdef WINDOWS
CLASS_DECL_BASE int32_t my_open(const char * psz, int32_t i);
CLASS_DECL_BASE FILE * my_fopen(const char * psz, const char * pszMode);
#else
CLASS_DECL_BASE void _get_errno(int32_t * perrno);
CLASS_DECL_BASE int32_t my_open(const char * psz, int32_t i);
CLASS_DECL_BASE FILE * my_fopen(const char * psz, const char * pszMode);
#endif



