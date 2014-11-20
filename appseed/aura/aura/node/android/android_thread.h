#pragma once


namespace android
{

   class CLASS_DECL_AURA thread :
      virtual public ::ansios::thread_impl
   {
   public:


      thread(::aura::application * papp);
      virtual ~thread();


   };


} // namespace android





