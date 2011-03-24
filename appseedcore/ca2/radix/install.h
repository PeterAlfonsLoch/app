#pragma once

namespace ca2
{

   class CLASS_DECL_ca install :
      public ::radix::object
   {
   public:
      void add_spa_start(const char * pszId);
      void remove_spa_start(const char * pszId);
      void add_app_install(const char * pszId);
   };

} // namespace ca2