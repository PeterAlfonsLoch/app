#pragma once


namespace ca4
{


   class CLASS_DECL_ca patch :
      public ::radix::object
   {
   public:
      // 0 for success
      int32_t bsdiff(const char * old, const char * newfile, const char * patch);

      // 0 for success
      int32_t bspatch(const char * old, const char * newfile, const char * patch);

      friend class application;
   };


} // namespace ca4

