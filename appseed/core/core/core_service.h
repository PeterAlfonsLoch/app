#pragma once

namespace core
{
   class CLASS_DECL_CORE service :
      public object
   {
   public:
      service();
      virtual ~service();
      int32_t stop(const char * pszName);
      int32_t remove(const char * pszName);
      using ::request_interface::create;
      int32_t create(
            const char * pszName,
            const char * pszDisplayName,
            const char * pszAuth);
      int32_t start(const char * pszName);
   };

} // namespace core
