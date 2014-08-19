#pragma once


namespace linux
{


   class CLASS_DECL_LINUX thread :
      virtual public ::ansios::thread_impl
   {
   public:


      thread(sp(::axis::application) papp);
      virtual ~thread();


   };



} // namespace linux


