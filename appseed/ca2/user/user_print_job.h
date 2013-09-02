#pragma once


namespace user
{

   class CLASS_DECL_ca2 print_job :
      virtual public ::ca2::print_job,
      virtual public ::user::job
   {
   public:

      sp(printer)     m_phprinter;

      print_job(sp(::application) papp);
      virtual ~print_job();


      virtual int32_t run();

   };

} // namespace user