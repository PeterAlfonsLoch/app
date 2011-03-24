#pragma once

namespace ca4
{

   class CLASS_DECL_ca compress :
      public ::radix::object
   {
   public:


      bool ungz(const char * lpcszUncompressed, const char * lpcszGzFileCompressed);
      bool gz(const char * lpcszGzFileCompressed, const char * lpcszUncompressed);

      bool ungz(ex1::output_stream & ostreamUncompressed, const char * lpcszGzFileCompressed);
      bool gz(ex1::output_stream & ostreamGzFileCompressed, const char * lpcszUncompressed);

      bool unbz(const char * lpcszUncompressed, const char * lpcszBzFileCompressed);
      bool bz(const char * lpcszBzFileCompressed, const char * lpcszUncompressed);

      bool unbz(ex1::output_stream & ostreamUncompressed, const char * lpcszBzFileCompressed);
      bool bz(ex1::output_stream & ostreamBzFileCompressed, const char * lpcszUncompressed);

      bool _compress(class primitive::memory & memory, void * pdata, unsigned long ulSizeUncompressed);
      bool _uncompress(primitive::memory & memoryUncompressed, primitive::memory & memoryCompressed, unsigned long ulSizeUncompressed);


      friend class application;


   };

} // namespace ca4



