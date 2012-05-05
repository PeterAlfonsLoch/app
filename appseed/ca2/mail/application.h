#pragma once


namespace mail
{


   class CLASS_DECL_ca2 application : 
      virtual public ::filehandler::application
   {
   public:
      

      application();
      virtual ~application();


      bool initialize_instance();

      BOOL exit_instance();

      virtual void update_pop3_mail_lists();

   };


} // namespace mail


