#pragma once


namespace ca
{

   class CLASS_DECL_ca print_job :
      virtual public ::ca::job
   {
   public:

      int      m_iPageStart;
      int      m_iPageCount;

      int      m_iPrintingPage;

      print_job(::ca::application * papp);
      virtual ~print_job();


      virtual int run() = 0;

   };

} // namespace ca