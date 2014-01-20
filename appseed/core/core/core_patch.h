#pragma once


namespace core
{


   class CLASS_DECL_CORE patch :
      public object
   {
   public:
      // 0 for success
      int32_t bsdiff(const char * old, const char * newfile, const char * patch);

      // 0 for success
      int32_t bspatch(const char * old, const char * newfile, const char * patch);

   };


} // namespace core

