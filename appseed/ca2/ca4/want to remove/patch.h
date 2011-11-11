#pragma once

namespace ca4
{

   class CLASS_DECL_ca2api00200002 patch :
      public base_object
   {
   public:
      // 0 for success
      int bsdiff(const char * old, const char * newfile, const char * patch);

      // 0 for success
      int bspatch(const char * old, const char * newfile, const char * patch);

      friend class application;
   };

} // namespace ca4