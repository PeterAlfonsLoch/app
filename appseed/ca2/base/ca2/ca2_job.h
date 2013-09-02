#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 job :
      virtual public ::ca2::thread
   {
   public:


      bool        m_bCancel;


      job(sp(::application) papp);
      virtual ~job();


      virtual int32_t run() = 0;


   };


} // namespace ca2


