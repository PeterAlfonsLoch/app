#include "StdAfx.h"
#include "html_application.h"
#include "win\win.h"
#include "resource.h"
#include "gen/CommandLineInfo.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "html_pane_view.h"
#include "wndfrm/FrameSchema.h"


html_application::html_application() :
    devedge::application_interface(this)
{
   m_pszAppName = (char * )malloc(100);
   strcpy((char *) m_pszAppName, "NetShareClient");
}

html_application::~html_application(void)
{
}


bool html_application::initialize_instance()
{
   if(!ca84::application::initialize_instance())
      return false;

   factory().set < a_view > ();
   factory().set < address_view > ();

   GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


   gen::CommandLineInfo cmdInfo;
   Ex1::GetApp()->_001ParseCommandLine(cmdInfo);

   SetRegistryKey("ca2core");

	
	m_ptemplate_main = new BaseSingleDocumentTemplate(
      this,
		"html/frame",
		&typeid(main_document),
		&typeid(main_frame),       // main SDI frame window
		&typeid(a_view));
   guibase::application::AddDocTemplate(m_ptemplate_main);

   m_ptemplate_html = new BaseSingleDocumentTemplate(
      this, 
      "html/frame", 
		&typeid(html_document), 
      &typeid(html_child_frame), 
		&typeid(html_view));

   m_ptemplate_html_edit = new BaseSingleDocumentTemplate(
      this, 
      "html/frame", 
		&typeid(html_document), 
      &typeid(html_child_frame), 
		&typeid(html_view));

   m_ptemplate_devedge = new BaseSingleDocumentTemplate(
      this, 
      "html/frame", 
      &typeid(devedge_document),
      &typeid(devedge_child_frame), 
		&typeid(devedge_view));


   if(cmdInfo.m_propertysetParameters.has_property("install_run"))
   {
      Application.install().remove_spa_start("html");
      install().add_app_install("html");
   }


	if (!_001ProcessShellCommand(cmdInfo))
		return false;

   return true;
}

BOOL html_application::exit_instance()
{
   return TRUE;
}

void html_application::bergedge_start()
{
   m_ptemplate_html->OpenDocumentFile(NULL);
}

Ex1FactoryImpl * html_application::Ex1AppGetFactoryImpl()
{
   return new WinFactoryImpl();
}

void html_application::_001OnFileNew()
{
   guibase::application::m_pdocmanager->OnFileNew();
}


bool html_application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
		
{
   return gen::application::_001OnCmdMsg(pcmdmsg);
}



CLASS_DECL_CA2_VERIVIEW ::ca::application * get_new_app()
{
   html_application * papp = new html_application;
   papp->m_hInstance = AfxGetApp()->m_hInstance;
   return papp;
}


::ca::application * html_application::get_app()
{
   return this;
}

void html_application::OnFileManagerOpenFile(
      FileManagerDDX & ddx, 
      FileManagerItemArray & itema)
{
   m_ptemplate_main->OpenDocumentFile(itema[0].m_strPath);
}


::ca::object * html_application::on_alloc(::ca::type_info & info)
{
	if(info == typeid(html::main_document))
	{
		return new html::main_document;
	}
	else if(info == typeid(html::main_frame))
	{
		return new html::main_frame(this);
	}
	else if(info == typeid(html_pane_view))
	{
		return new html_pane_view(this);
	}
	return ca77::application::on_alloc(info);
}