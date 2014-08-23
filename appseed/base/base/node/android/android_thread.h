#pragma once


namespace android
{

   class CLASS_DECL_BASE thread :
      virtual public ::ansios::thread_impl
   {
   public:


      thread(sp(::aura::application) papp);
      virtual ~thread();


   };


} // namespace android





