#pragma once

namespace ca4
{

   class CLASS_DECL_ca compress :
      public ::radix::object
   {
   public:


      bool ungz(const char * lpcszUncompressed, const char * lpcszGzFileCompressed);
      bool gz(const char * lpcszGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(ex1::writer & ostreamUncompressed, const char * lpcszGzFileCompressed);
      bool gz(ex1::writer & ostreamGzFileCompressed, const char * lpcszUncompressed);

      bool unbz(const char * lpcszUncompressed, const char * lpcszBzFileCompressed);
      bool bz(const char * lpcszBzFileCompressed, const char * lpcszUncompressed);

      bool unbz(ex1::writer & ostreamUncompressed, const char * lpcszBzFileCompressed);
      bool bz(ex1::writer & ostreamBzFileCompressed, const char * lpcszUncompressed);

      bool bz_stream(ex1::writer & ostreamBzFileCompressed, ex1::reader & istreamFileUncompressed);

      bool _compress(class primitive::memory & memory, void * pdata, unsigned long ulSizeUncompressed);
      bool _uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, unsigned long ulSizeUncompressed);


      static bool null(ex1::writer & ostream, ex1::reader & istream);


      count extract_all(const char * pszFile, ::ca::application * papp);


      friend class application;


   };

} // namespace ca4



