#pragma once


void CLASS_DECL_CA2_TESSERACT KickDevEdgeFront(::ca::application * papp);

namespace netnode
{
   class bergedge_document;
}
class netnodeScriptManager;

namespace devedge
{

   class pane_view;

   class CLASS_DECL_CA2_TESSERACT application :
      virtual public ::tesseract::simpledbcfg::application,
      virtual public ::ca::interface_application < devedge::application_interface >
   {
   public:


      ::collection::map < int, int, netnode::bergedge_document *, netnode::bergedge_document * > m_mapEdge;
      pane_view * m_ppaneview;


      application(void);
      virtual ~application(void);


      virtual void construct();


      bool initialize_instance();
      BOOL exit_instance();

      virtual void pre_translate_message(gen::signal_object * pobj);

      virtual void on_request(::ca::create_context * pcreatecontext);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);

      virtual bool on_install();
   };


} // namespace devedge