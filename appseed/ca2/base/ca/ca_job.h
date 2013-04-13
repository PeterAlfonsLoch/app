#pragma once


namespace ca
{


   class CLASS_DECL_ca2 job :
      virtual public ::ca::thread
   {
   public:


      bool        m_bCancel;


      job(sp(::ca::application) papp);
      virtual ~job();


      virtual int32_t run() = 0;


   };


} // namespace ca


