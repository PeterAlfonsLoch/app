#pragma once


namespace linux
{


   class CLASS_DECL_LINUX thread :
      virtual public ::thread_impl
   {
   public:


      thread(sp(::base::application) papp);
      virtual ~thread();






