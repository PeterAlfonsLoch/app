#pragma once


namespace user
{

   class CLASS_DECL_ca2 print_job :
      virtual public ::ca::print_job,
      virtual public ::user::job
   {
   public:

      ph(printer)     m_phprinter;

      print_job(::ca::application * papp);
      virtual ~print_job();


      virtual int32_t run();

   };

} // namespace user