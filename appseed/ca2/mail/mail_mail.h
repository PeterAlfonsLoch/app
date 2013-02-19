#pragma once


namespace mail
{


   class CLASS_DECL_ca2 mail : 
      virtual public ::ca::section
   {
   public:
      

      mail();
      virtual ~mail();


      bool initialize_instance();

      virtual int32_t exit_instance();

      virtual void update_pop3_mail_lists();

   };


} // namespace mail


