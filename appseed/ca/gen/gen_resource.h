#pragma once

#define _RESID_BASE                  0xD800
#define _STRING_BASE                  _RESID_BASE

#define _IDS_DATETIME_INVALID         (_STRING_BASE + 0)
#define _IDS_DATETIMESPAN_INVALID      (_STRING_BASE + 1)

#define _SERVICE_MANAGER_OPEN_ERROR      (_STRING_BASE + 10)
#define _SERVICE_START_ERROR            (_STRING_BASE + 11)
#define _SERVICE_OPEN_ERROR            (_STRING_BASE + 12)
#define _SERVICE_DELETE_ERROR         (_STRING_BASE + 13)
#define _SERVICE_STOP_ERROR            (_STRING_BASE + 14)


#pragma once

namespace gen
{

   class CLASS_DECL_ca resource :
      virtual public ::gen::object
   {
   public:
      resource();
      virtual ~resource();

      virtual bool ReadResource(gen::file & file, UINT nID, const char * lpcszType);
      virtual bool ReadResource(HINSTANCE hinst, gen::file & file, UINT nID, const char * lpcszType);

   };

   typedef ca::smart_pointer < resource > resource_sp;

} // namespace gen

