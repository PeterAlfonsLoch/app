#pragma once

namespace ca2
{
   class CLASS_DECL_ca service :
      public ::radix::object
   {
   public:
      service();
      virtual ~service();
      int stop(const char * pszName);
      int remove(const char * pszName);
      using ::ex1::request_interface::create;
      int create(
            const char * pszName,
            const char * pszDisplayName,
            const char * pszVotagus);
      int start(const char * pszName);
   };

} // namespace ca2