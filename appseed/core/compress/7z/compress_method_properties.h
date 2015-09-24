// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once

namespace libcompress
{

   struct method
   {
     method_id Id;
     ::ca::property_set Props;
   };

   struct method_mode
   {
     array_ptr_alloc < method > methods;
     uint32 NumThreads;

     method_mode()
         : NumThreads(1)
     {
     }
     bool is_empty() const
     {
        return methods.is_empty() ;
     }
   };

   HRESULT SetMethodProperties(const method &method, const file_size_t *inSizeForReduce, ::ca::ca * coder);

} // namespace libcompress
