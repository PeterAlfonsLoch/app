#pragma once


namespace ca2
{

   class CLASS_DECL_ca2 print_job :
      virtual public ::ca2::job
   {
   public:

      int32_t      m_iPageStart;
      int32_t      m_iPageCount;

      int32_t      m_iPrintingPage;

      print_job(sp(::application) papp);
      virtual ~print_job();


      virtual int32_t run() = 0;

   };

} // namespace ca2
