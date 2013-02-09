// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once


namespace libcompress
{


   struct method
   {


      method_id Id;
      gen::property_set Props;


   };


   struct method_mode
   {


      array_ptr_alloc < method > methods;

      uint32_t NumThreads;


      method_mode()
         : NumThreads(1)
      {
      }


      bool is_empty() const
      {
         return methods.is_empty() ;
      }


   };


   CLASS_DECL_ca HRESULT SetMethodProperties(const method &method, const file_size *inSizeForReduce, ::ca::ca * coder);


} // namespace libcompress



