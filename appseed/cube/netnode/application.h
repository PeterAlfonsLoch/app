#pragma once

class netnodeScriptManager;
class netnodeService;

namespace netnode
{

   class CLASS_DECL_CA2_CUBE application :
      public ::whiteboard::application
   {
   public:
      application(void);
      virtual ~application(void);
      virtual void construct();


      netnodeService * m_pservice;

      virtual void netnode_run();

      bool initialize_instance();
      BOOL ExitInstance();

      virtual int run();

      int CreateService();
      int RemoveService();

      netnodeScriptManager * m_pscriptmanager;
      ::userbase::multiple_document_template * m_ptemplateEdge;

      netnodeScriptManager * get_script_manager();

      void get_Votagus_folder(string &str);

      using ::ca84::application::process;
      void process(machine_event_data * pdata);

      //void sync_load_url(const char * lpcszFile, const char * lpcszHost, const char * lpcszUri);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
         
      virtual void pre_translate_message(gen::signal_object * pobj);

      virtual bool does_launch_window_on_startup();

      virtual void on_request(var & varFile, var & varQuery);

   };


} // namespace netnode