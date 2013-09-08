#pragma once


namespace core
{


   class CLASS_DECL_ca2 patch :
      public object
   {
   public:
      // 0 for success
      int32_t bsdiff(const char * old, const char * newfile, const char * patch);

      // 0 for success
      int32_t bspatch(const char * old, const char * newfile, const char * patch);

   };


} // namespace core

