#include "StdAfx.h"


namespace md5
{

   application::application(void)
   {
      m_strAppName = "md5"; // dedicado ao Telmo Friesen Almirante Tamandaré
      m_strBaseSupportId = "votagus_ca2_paint";
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
   
      factory().creatable < md5::document >();
      factory().creatable < md5::view >();
      factory().creatable < md5::frame >();

      if(!ca84::application::initialize_instance())
         return false;

	   userbase::single_document_template * pdocumenttemplate;
	   pdocumenttemplate = new userbase::single_document_template(
         this,
		   "md5",
		   typeid(md5::document),
		   typeid(md5::frame),
		   typeid(md5::view));
      userbase::application::add_document_template(pdocumenttemplate);
      m_ptemplateAlarm = pdocumenttemplate;

	   userbase::multiple_document_template * pmultipledocumenttemplate = new userbase::multiple_document_template(
         this,
		   "md5",
		   typeid(md5::document),
		   typeid(md5::frame),
		   typeid(md5::view));
      m_ptemplateAlatel = pmultipledocumenttemplate;


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
         FileManagerItemArray & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      m_ptemplate_html->open_document_file(itema[0].m_strPath);
   }

   ::document * application::_001OpenDocumentFile(var varFile)
   {
      return m_ptemplateAlarm->open_document_file(varFile, true, m_puiInitialPlaceHolderContainer);
   }


} // namespace md5


CLASS_DECL_CA2_MD5 ::ca::application * get_new_app()
{
   return new md5::application;
}


