#pragma once


namespace user
{

   class CLASS_DECL_CORE print_job :
      virtual public ::print_job,
      virtual public ::job
   {
   public:

      
      sp(printer)       m_phprinter;
      view *            m_pview;


      print_job(sp(base_application) papp);
      virtual ~print_job();


      virtual int32_t run();


   };


} // namespace user



