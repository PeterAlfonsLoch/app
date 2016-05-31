#pragma once


namespace primitive
{

   enum e_command
   {

      command_default,
      command_on_agree_exit,
      command_france_exit,
      command_check_exit

   };




   class CLASS_DECL_ACE command :
      virtual public ::object
   {
   public:


      e_command         m_ecommand;


      command(::ace::application * papp);
      command(::ace::application * papp, e_command ecommand);
      virtual ~command();

      virtual var run();


      virtual void on_request(sp(::create) pcreationcontext);


      virtual string get_description();


   };


} // namespace primitive

