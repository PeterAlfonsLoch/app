#pragma once


namespace ca
{


   class CLASS_DECL_ca command :
      virtual public ::ca::object,
      virtual public ::ca::request_interface
   {
   public:

      
      command(::ca::application * papp);
      virtual ~command();

      virtual var run();


      virtual void on_request(::ca::create_context * pcreationcontext);


      virtual string get_description();


   };


} // namespace command



#pragma once


namespace ca
{


   class application;


} // namespace ca


class command_target;


class CLASS_DECL_ca base_cmd_ui :
   public ca::signal_object
{
public:


   cmd_ui * m_pcmdui;


   base_cmd_ui(ca::signal * psignal);


};


class CLASS_DECL_ca BaseCommand :
   public ca::signal_object
{
public:


   id   m_id;


   BaseCommand(ca::signal * psignal);


};


class CLASS_DECL_ca BaseCmdMsg :
   public ::ca::object
{
public:


   enum e_type
   {
      type_command,
      type_cmdui
   };


   cmd_ui  *                                    m_pcmdui;
   id                                           m_id;
   e_type                                       m_etype;
   comparable_array < ::command_target * >      m_commandtargetptraHandle;


   BaseCmdMsg();
   BaseCmdMsg(id id);
   BaseCmdMsg(cmd_ui * pcmdui);


   bool handle(::command_target * pcommandtarget);
   bool is_handled(::command_target * pcommandtarget);


};


