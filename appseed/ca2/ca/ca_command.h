#pragma once


namespace ca
{


   class CLASS_DECL_ca2 command :
      virtual public ::ca::object,
      virtual public ::ca::request_interface
   {
   public:

      
      command(sp(::ca::application) papp);
      virtual ~command();

      virtual var run();


      virtual void on_request(sp(::ca::create_context) pcreationcontext);


      virtual string get_description();


   };


} // namespace command



#pragma once


namespace ca
{


   class application;


} // namespace ca


class command_target;


class CLASS_DECL_ca2 base_cmd_ui :
   public ::ca::signal_object
{
public:


   cmd_ui * m_pcmdui;


   base_cmd_ui(::ca::signal * psignal);


};


class CLASS_DECL_ca2 BaseCommand :
   public ::ca::signal_object
{
public:


   id   m_id;


   BaseCommand(::ca::signal * psignal);


};


class CLASS_DECL_ca2 BaseCmdMsg :
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


