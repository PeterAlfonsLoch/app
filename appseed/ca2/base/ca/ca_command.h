#pragma once


namespace ca2
{


   class CLASS_DECL_ca2 command :
      virtual public ::ca2::object,
      virtual public ::ca2::request_interface
   {
   public:

      
      command(sp(::ca2::application) papp);
      virtual ~command();

      virtual var run();


      virtual void on_request(sp(::ca2::create_context) pcreationcontext);


      virtual string get_description();


   };


} // namespace command



#pragma once


namespace ca2
{


   class application;


} // namespace ca2


class command_target;


class CLASS_DECL_ca2 base_cmd_ui :
   public ::ca2::signal_object
{
public:


   cmd_ui * m_pcmdui;


   base_cmd_ui(::ca2::signal * psignal);


};


class CLASS_DECL_ca2 BaseCommand :
   public ::ca2::signal_object
{
public:


   id   m_id;


   BaseCommand(::ca2::signal * psignal);


};


class CLASS_DECL_ca2 BaseCmdMsg :
   public ::ca2::object
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


