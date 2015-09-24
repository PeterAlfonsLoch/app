// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once


namespace libcompress
{


   struct method :
      virtual public element
   {


      method_id Id;
      property_set Props;


   };


   struct method_mode
   {


      spa(method) methods;

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


   CLASS_DECL_CORE HRESULT SetMethodProperties(const method &method, const file_size_t *inSizeForReduce, sp(element) coder);


} // namespace libcompress



