#pragma once


namespace usermail
{


   class CLASS_DECL_CORE usermail : 
      virtual public ::base_departament
   {
   public:
      

      usermail(::base::application * papp);
      virtual ~usermail();


      bool initialize_instance();

      virtual int32_t exit_instance();

      virtual void update_pop3_mail_lists();

   };


} // namespace usermail


