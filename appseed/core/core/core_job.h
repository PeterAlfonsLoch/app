#pragma once


namespace core
{


   class CLASS_DECL_ca2 job :
      virtual public ::core::thread
   {
   public:


      bool        m_bCancel;


      job(sp(base_application) papp);
      virtual ~job();


      virtual int32_t run() = 0;


   };


} // namespace core


