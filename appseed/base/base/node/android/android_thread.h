#pragma once


namespace android
{

   class CLASS_DECL_BASE thread :
      virtual public ::ansios::thread_impl
   {
   public:




      thread(sp(::base::application) papp);
      virtual ~thread();







      virtual void defer_process_windows_messages();


   };


} // namespace android





