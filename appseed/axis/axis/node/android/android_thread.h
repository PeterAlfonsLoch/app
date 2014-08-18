#pragma once


namespace android
{

   class CLASS_DECL_AXIS thread :
      virtual public ::ansios::thread_impl
   {
   public:


      thread(sp(::axis::application) papp);
      virtual ~thread();


   };


} // namespace android





