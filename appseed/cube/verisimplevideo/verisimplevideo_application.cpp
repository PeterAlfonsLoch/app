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

      if(!ca84::application::initialize_instance())
         return false;

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";


      gen::command_line cmdInfo;
      _001ParseCommandLine(cmdInfo);

      SetRegistryKey("ca2core");

      ::userbase::single_document_template* pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         &typeid(html_document),
         &typeid(html_frame),       // main SDI frame ::ca::window
         &typeid(pane_view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplate_html = pDocTemplate;
      pDocTemplate = new ::userbase::single_document_template(
         this,
         "html/frame",
         &typeid(verisimplevideo::document),
         &typeid(verisimplevideo::frame),       // main SDI frame ::ca::window
         &typeid(verisimplevideo::view));
      userbase::application::add_document_template(pDocTemplate);
      m_ptemplateVideo = pDocTemplate;



      return true;
   }

   BOOL application::exit_instance()
   {
      return TRUE;
   }

   bool application::bergedge_start()
   {
      if(m_ptemplate_html->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer) == NULL)
         return false;
      return ca84::application::bergedge_start();
   }

   void application::_001OnFileNew()
   {
      m_ptemplate_html->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer);
   }


   ::document * application::_001OpenDocumentFile(var varFile)
   {
      return m_ptemplateVideo->open_document_file(varFile, TRUE, System.m_puiInitialPlaceHolderContainer);
   }



   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)
         
   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }





   ::ca::application * application::get_app() const
   {
      return m_papp;
   }

   void application::on_request(var & varFile, var & varQuery)
   {
      
      m_ptemplate_html->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer);

      string str;
      if(varFile.get_type() == var::type_string)
      {
         str = varFile;
      }
      else
      {
         if(varFile.stra().get_count() > 0)
         {
            str = varFile.stra()[0];
         }
      }
      m_ptemplateVideo->open_document_file(str, TRUE, System.m_puiInitialPlaceHolderContainer);
   }


   bool application::on_install()
   {
      string strFormat;

      win::registry::Key keyKar(HKEY_CLASSES_ROOT, ".flv", true);
      keyKar.SetValue(NULL, "veriwell.video.studio.file");

      win::registry::Key keyLink4(HKEY_CLASSES_ROOT, "veriwell.video.studio.file\\DefaultIcon", true);
      strFormat = System.dir().matter("mplite/mainframe/doc.ico");
      keyLink4.SetValue(NULL, strFormat);

      win::registry::Key keyLink3(HKEY_CLASSES_ROOT, "veriwell.video.studio.file\\shell", true);
      keyLink3.SetValue(NULL, "open");

      win::registry::Key keyLink2(HKEY_CLASSES_ROOT, "veriwell.video.studio.file\\shell\\open", true);
      keyLink2.SetValue(NULL, "&open");

      win::registry::Key keyLink1(HKEY_CLASSES_ROOT, "veriwell.video.studio.file\\shell\\open\\command", true);

      strFormat.Format("\"%s\" \"%%L\"", System.dir().ca2module("cubeapp.exe"));
      keyLink1.SetValue(NULL, strFormat);

      return ca2::application::on_install();
   }


} // namespace verisimplevideo

