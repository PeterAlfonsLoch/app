#pragma once


namespace axis
{


   class CLASS_DECL_AXIS compress :
      public object
   {
   public:


      bool ungz(::aura::application * papp,const ::file::path & lpcszUncompressed,const ::file::path & lpcszGzFileCompressed);
      bool gz(::aura::application * papp,const ::file::path & lpcszGzFileCompressed,const ::file::path & lpcszUncompressed);

      bool ungz(::file::ostream & ostreamUncompressed,const ::file::path & lpcszGzFileCompressed);
      bool gz(::file::ostream & ostreamGzFileCompressed,const ::file::path & lpcszUncompressed);

      bool ungz(::file::memory_buffer & memoryfile);

      bool unbz(::aura::application * papp,const ::file::path & lpcszUncompressed,const ::file::path & lpcszBzFileCompressed);
      bool bz(::aura::application * papp,const ::file::path & lpcszBzFileCompressed,const ::file::path & lpcszUncompressed);

      bool unbz(::file::ostream & ostreamUncompressed, const ::file::path & lpcszBzFileCompressed);
      bool bz(::file::ostream & ostreamBzFileCompressed,const ::file::path & lpcszUncompressed);

      bool bz_stream(::file::ostream & ostreamBzFileCompressed, ::file::istream & istreamFileUncompressed);

      bool _compress(class primitive::memory & memory, void * pdata, ::primitive::memory_size ulSizeUncompressed);
      bool _uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, ::primitive::memory_size ulSizeUncompressed);

      bool null(::file::ostream & ostream, ::file::istream & istream);

      void extract_all(const ::file::path & pszFile, ::aura::application * papp);

      void zip(const ::file::path & pszZip,const ::file::path & psz,::aura::application * papp);
      void zip(const ::file::path & psz,::aura::application * papp);


   };


} // namespace axis



//#ifdef WINDOWS
//CLASS_DECL_AXIS int32_t my_open(const char * psz, int32_t i);
//CLASS_DECL_AXIS FILE * my_fopen(const char * psz, const char * pszMode);
//#else
//CLASS_DECL_AXIS void _get_errno(int32_t * perrno);
//CLASS_DECL_AXIS int32_t my_open(const char * psz, int32_t i);
//CLASS_DECL_AXIS FILE * my_fopen(const char * psz, const char * pszMode);
//#endif



