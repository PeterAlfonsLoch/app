#pragma once


namespace ca
{


   class CLASS_DECL_ca job :
      virtual public ::gen::thread
   {
   public:


      bool        m_bCancel;


      job(::ca::application * papp);
      virtual ~job();


      virtual int32_t run() = 0;


   };


} // namespace ca


