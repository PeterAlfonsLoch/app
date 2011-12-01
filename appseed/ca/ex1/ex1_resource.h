#pragma once

namespace ex1
{

   class CLASS_DECL_ca resource :
      virtual public ::radix::object
   {
   public:
      resource();
      virtual ~resource();

      virtual bool ReadResource(ex1::file & file, UINT nID, const char * lpcszType);
      virtual bool ReadResource(HINSTANCE hinst, ex1::file & file, UINT nID, const char * lpcszType);

   };

   typedef ca::smart_pointer < resource > resource_sp;

} // namespace ex1