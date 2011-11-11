#pragma once

namespace ca4
{

   class CLASS_DECL_ca2api00200002 compress :
      public base_object
   {
   public:
      void ungz(const char * lpcszUncompressed, const char * lpcszGzFileCompressed);
      void gz(const char * lpcszGzFileCompressed, const char * lpcszUncompressed);

      friend class application;
   };


} // namespace ca4