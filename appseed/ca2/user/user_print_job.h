#pragma once


namespace user
{

   class CLASS_DECL_ca print_job :
      virtual public ::ax::print_job,
      virtual public ::user::job
   {
   public:

      ph(printer)     m_phprinter;

      print_job(::ax::application * papp);
      virtual ~print_job();


      virtual int run();

   };

} // namespace user