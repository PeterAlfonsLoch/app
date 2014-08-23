#pragma once


namespace linux
{


   class CLASS_DECL_LINUX thread :
      virtual public ::ansios::thread_impl
   {
   public:


      thread(sp(::aura::application) papp);
      virtual ~thread();


   };



} // namespace linux


