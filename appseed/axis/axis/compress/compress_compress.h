#pragma once


namespace axis
{


   class CLASS_DECL_AXIS compress :
      public object
   {
   public:


      bool compress(class memory & memory, void * pdata, memory_size_t ulSizeUncompressed);
      bool uncompress(memory & memoryUncompressed, memory & memoryCompressed);


      bool gz(::aura::application * papp, const ::file::path & lpcszGzFileCompressed, const ::file::path & lpcszUncompressed, int iLevel = 6);
      bool gz(::aura::application * papp, const ::file::file * pfileOut, const ::file::path & lpcszUncompressed, int iLevel = 6);
      bool gz(::aura::application * papp, const ::file::file * pfileOut, const ::file::file * pfileIn, int iLevel = 6);


      bool ungz(::aura::application * papp, const ::file::path & lpcszUncompressed,const ::file::path & lpcszGzFileCompressed);
      bool ungz(::aura::application * papp, ::file::ostream & ostreamUncompressed,const ::file::path & lpcszGzFileCompressed);
      bool ungz(::aura::application * papp, ::file::file * pfileOut, ::file::file * pfileIn);


      bool ungz(::file::ostream & ostreamUncompressed, ::file::istream & istreamGzFileCompressed);

      bool bz(::aura::application * papp, const ::file::path & lpcszBzFileCompressed, const ::file::path & lpcszUncompressed, int iBlockSize = 9, int iVerbosity = 0, int iWorkFactor = 0);
      bool bz(::aura::application * papp, ::file::ostream & ostreamBzFileCompressed, ::file::istream & istreamUncompressed, int iBlockSize = 9, int iVerbosity = 0, int iWorkFactor = 0);

      bool unbz(::aura::application * papp,const ::file::path & lpcszUncompressed,const ::file::path & lpcszBzFileCompressed);
      bool unbz(::aura::application * papp, ::file::ostream & ostreamUncompressed, const ::file::path & lpcszBzFileCompressed);

      bool unbz(::file::ostream & ostreamUncompressed, ::file::istream & istreamBzFileCompressed);


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



