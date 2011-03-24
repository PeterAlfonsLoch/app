#include "StdAfx.h"


namespace alarm
{

   application::application(void)
   {
      m_strAppName = "alarm"; // dedicado ao Telmo Friesen Almirante Tamandaré
      m_strBaseSupportId = "votagus_ca2_paint";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
   
      factory().creatable_small < alarm::document >();
      factory().creatable_small < alarm::view >();
      factory().creatable_small < alarm::frame >();
      factory().creatable_small < alarm::pane_view >();
      factory().creatable_small < alatel::document >();
      factory().creatable_small < alatel::view >();
      factory().creatable_small < alatel::frame >();
      factory().creatable_small < alatel::week_view >();
      factory().creatable_small < alatel::alarm_list_view >();

      if(!ca84::application::initialize_instance())
         return false;

	   userbase::single_document_template * pdocumenttemplate;
	   pdocumenttemplate = new userbase::single_document_template(
         this,
		   "alarm",
		   typeid(alarm::document),
		   typeid(alarm::frame),
		   typeid(alarm::pane_view));
      userbase::application::add_document_template(pdocumenttemplate);
      m_ptemplateAlarm = pdocumenttemplate;

	   pdocumenttemplate = new userbase::single_document_template(
         this,
		   "alatel",
		   typeid(alatel::document),
		   typeid(alatel::frame),
		   typeid(alatel::view));
      m_ptemplateAlatel = pdocumenttemplate;

	   pdocumenttemplate = new userbase::single_document_template(
         this,
		   "alatel",
		   typeid(alatel::document),
		   typeid(alatel::frame),
		   typeid(alatel::week_view));
      m_ptemplateAlatelByWeekday = pdocumenttemplate;

      return TRUE;
   }

   int application::exit_instance()
   {
      return 0;
   }

   bool application::bergedge_start()
   {
	   if (!_001ProcessShellCommand(command_line()))
		   return FALSE;
      return true;
   }

   void application::_001OnFileNew()
   {
      m_ptemplateAlarm->open_document_file(NULL, TRUE, m_puiInitialPlaceHolderContainer);
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
   {
      return cube::application::_001OnCmdMsg(pcmdmsg);
   }

   void application::OnFileManagerOpenFile(
         ::filemanager::data * pdata, 
         ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplate_html->open_document_file(itema[0].m_strPath);
   }


} // namespace alarm


CLASS_DECL_CA2_ALARM ::ca::application * get_new_app()
{
   return new alarm::application;
}


