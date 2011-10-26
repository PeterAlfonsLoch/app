#include "StdAfx.h"
#include "application.h"
#include "html/html_frame.h"
#include "html/html_document.h"
#include "html/html_view.h"
#include "pane_view.h"

namespace verisimplevideo
{


   application::application()
   {
   }


   void application::construct()
   {
      m_strAppName         = "verisimplevideo";
      m_strBaseSupportId   = "votagus_ca2_paint";
      m_strInstallToken    = "verisimplevideo";    
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {






















      System.factory().creatable_small < verisimplevideo::pane_view >();
      System.factory().creatable_small < verisimplevideo::document >();
      System.factory().creatable_small < verisimplevideo::frame >();
      System.factory().creatable_small < verisimplevideo::view >();

      if(!cube2::application::initialize_instance())
         return false;
      if(!mediamanager::mediamanager_container::initialize_container(this))
         return false;

      if(!mediaplaylist::central_container::initialize(this))
         return false;

      if(!midi_central_container::initialize_central_container(this))
      {
         return false;
      }

      if(!MusicalPlayerCentralContainer::Initialize(this))
      {
         return false;
      }

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";




      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         ::ca::get_type_info < html_document > (),
         ::ca::get_type_info < html_frame > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < pane_view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         ::ca::get_type_info < verisimplevideo::document > (),
         ::ca::get_type_info < verisimplevideo::frame > (),       // main SDI frame ::ca::window
         ::ca::get_type_info < verisimplevideo::view > ());
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateVideo = pDocTemplate;



      return true;
   }


   void application::on_request(::ca::create_context * pcreatecontext)
   {
      if(m_ptemplate_html->get_document() == NULL)
      {
         m_ptemplate_html->open_document_file(pcreatecontext);
      }
      if(!pcreatecontext->m_spCommandLine->m_varFile.is_empty())
      {
         m_ptemplate_html->get_document()->get_typed_view < verisimplevideo::pane_view > ()->set_cur_tab_by_id(verisimplevideo::PaneViewVideo);
         m_ptemplateVideo->open_document_file(pcreatecontext->m_spCommandLine->m_varFile);
      }
   }



   bool application::on_install()
   {
      string strFormat;

      win::registry::Key keyKar(HKEY_CLASSES_ROOT, ".flv", true);
      keyKar.SetValue(NULL, "veriwell.video.studio.file");

      win::registry::Key keyLink4(HKEY_CLASSES_ROOT, "veriwell.video.studio.file\\DefaultIcon", true);
      strFormat = Application.dir().matter("mplite/mainframe/doc.ico");
      keyLink4.SetValue(NULL, strFormat);

      win::registry::Key keyLink3(HKEY_CLASSES_ROOT, "veriwell.video.studio.file\\shell", true);
      keyLink3.SetValue(NULL, "open");

      win::registry::Key keyLink2(HKEY_CLASSES_ROOT, "veriwell.video.studio.file\\shell\\open", true);
      keyLink2.SetValue(NULL, "&open");

      win::registry::Key keyLink1(HKEY_CLASSES_ROOT, "veriwell.video.studio.file\\shell\\open\\command", true);

      strFormat.Format("\"%s\" \"%%L\"", System.dir().ca2module("ca2app.exe"));
      keyLink1.SetValue(NULL, strFormat);

      return ca2::application::on_install();
   }


} // namespace verisimplevideo

