#pragma once


namespace ca
{


   class CLASS_DECL_ca job :
      virtual public ::radix::thread
   {
   public:


      bool        m_bCancel;


      job(::ca::application * papp);
      virtual ~job();


      virtual int run() = 0;


   };


} // namespace ca


