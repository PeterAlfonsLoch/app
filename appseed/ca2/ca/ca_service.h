#pragma once

namespace ca
{
   class CLASS_DECL_ca service :
      public ::ca::object
   {
   public:
      service();
      virtual ~service();
      int32_t stop(const char * pszName);
      int32_t remove(const char * pszName);
      using ::ca::request_interface::create;
      int32_t create(
            const char * pszName,
            const char * pszDisplayName,
            const char * pszAuth);
      int32_t start(const char * pszName);
   };

} // namespace ca