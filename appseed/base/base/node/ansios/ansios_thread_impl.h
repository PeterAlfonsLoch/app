#pragma once


namespace ansios
{


   class CLASS_DECL_BASE thread_impl:
      virtual public ::thread_impl
   {
   public:




      thread_impl(sp(::base::application) papp);
      virtual ~thread_impl();


      operator pthread_t() const;
      

   };


} // namespace ansios









