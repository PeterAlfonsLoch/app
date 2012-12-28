#pragma once


namespace ca
{

   class CLASS_DECL_ca print_job :
      virtual public ::ca::job
   {
   public:

      int32_t      m_iPageStart;
      int32_t      m_iPageCount;

      int32_t      m_iPrintingPage;

      print_job(::ca::application * papp);
      virtual ~print_job();


      virtual int32_t run() = 0;

   };

} // namespace ca