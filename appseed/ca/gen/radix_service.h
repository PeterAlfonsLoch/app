#pragma once

namespace ca2
{
   class CLASS_DECL_ca service :
      public ::radix::object
   {
   public:
      service();
      virtual ~service();
      int32_t stop(const char * pszName);
      int32_t remove(const char * pszName);
      using ::ex1::request_interface::create;
      int32_t create(
            const char * pszName,
            const char * pszDisplayName,
            const char * pszVotagus);
      int32_t start(const char * pszName);
   };

} // namespace ca2