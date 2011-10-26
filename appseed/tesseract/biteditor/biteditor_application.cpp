#include "StdAfx.h"
#include "biteditor_application.h"
#include "biteditor_document.h"
#include "biteditor_frame.h"
#include "biteditor_view.h"
#include "main_document.h"
#include "biteditor_child_frame.h"
#include "front_child_frame.h"
#include "front_document.h"
#include "front_view.h"

biteditor_application::biteditor_application()
{
}

void biteditor_application::construct()
{
   m_strAppName         = "biteditor";
   m_strBaseSupportId   = "votagus_ca2_biteditor";
   m_strInstallToken    = "biteditor";
}

biteditor_application::~biteditor_application()
{
}

bool biteditor_application::initialize_instance()
{
   System.factory().creatable_small < main_document > ();
   System.factory().creatable_small < biteditor_frame > ();
   System.factory().creatable_small < biteditor::tab_view > ();
   System.factory().creatable_small < biteditor_document > ();
   System.factory().creatable_small < biteditor_child_frame > ();
   System.factory().creatable_small < biteditor_view > ();

   if(!cube2::application::initialize_instance())
      return false;

   ::CoInitialize(NULL);

   m_ptemplateEdge = new ::userbase::single_document_template(
      this, 
      "biteditor/frame", 
      ::ca::get_type_info < main_document > (), 
      ::ca::get_type_info < biteditor_frame > (), 
      ::ca::get_type_info < biteditor::tab_view > ());

   m_ptemplate_devedge = new ::userbase::single_document_template(
      this, 
      "biteditor/frame", 
      ::ca::get_type_info < biteditor_document > (), 
      ::ca::get_type_info < biteditor_child_frame > (), 
      ::ca::get_type_info < biteditor_view > ());

   m_ptemplateFront = new ::userbase::single_document_template(
      this, 
      "biteditor/frame", 
      ::ca::get_type_info < front_document > (), 
      ::ca::get_type_info < front_child_frame > (), 
      ::ca::get_type_info < front_view > ());

   GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


   return true;
}


void biteditor_application::on_request(::ca::create_context * pcreatecontext)
{

   if(m_ptemplateEdge->get_document() == NULL)
   {
      m_ptemplateEdge->open_document_file(pcreatecontext);
   }
   m_ptemplate_devedge->open_document_file(pcreatecontext);

}



