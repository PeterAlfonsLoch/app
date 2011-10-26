#pragma once

class CLASS_DECL_CA2_VERIVIEW html_application :
   public ca84::application,
   public devedge::application_interface
{
public:
	// DECLARE_DYNAMIC(html_application)
   html_application(void);
   virtual ~html_application(void);

   BaseSingleDocumentTemplate *  m_ptemplate_main;
   BaseSingleDocumentTemplate *  m_ptemplate_html;
   BaseSingleDocumentTemplate *  m_ptemplate_html_edit;
   BaseDocumentTemplate *        m_ptemplate_devedge;

   bool initialize_instance();
   BOOL exit_instance();

   void bergedge_start();

   void _001OnFileNew();

   Ex1FactoryImpl * Ex1AppGetFactoryImpl();
	virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg);
		

   virtual ::ca::application * get_app();
   void OnFileManagerOpenFile(
      FileManagerDDX & ddx, 
      FileManagerItemArray & itema);

   virtual ::ca::object * on_alloc(::ca::type_info & info);

};
