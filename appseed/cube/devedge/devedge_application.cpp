#include "StdAfx.h"
#include "pane_view.h"

void KickNetNodeThread();

namespace devedge 
{

   application::application()
   {
   }

   void application::construct()
   {
      m_pscriptmanager     = NULL;
      m_strAppName         = "devedge";
      m_strBaseSupportId   = "votagus_ca2_devedge";
      m_strInstallToken    = "devedge";
      m_ppaneview          = NULL;
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < devedge::solution_document > ();
      System.factory().cloneable_small < devedge::solution_view > ();
      System.factory().cloneable_small < devedge::project > ();
      System.factory().cloneable_small < devedge::folder > ();
      System.factory().cloneable_small < devedge::headers > ();
      System.factory().cloneable_small < devedge::source > ();
      System.factory().cloneable_small < devedge::file > ();

      if(!ca84::application::initialize_instance())
         return false;

      devedge::application_interface::m_ptemplateEdge = new ::userbase::single_document_template(
         this, 
         "devedge/frame", 
         &typeid(MainDoc), 
         &typeid(main_frame), 
         &typeid(devedge::pane_view));

      add_document_template(devedge::application_interface::m_ptemplateEdge);

      devedge::application_interface::m_ptemplate_devedge = new ::userbase::multiple_document_template(
         this, 
         "devedge/frame", 
         &typeid(document), 
         &typeid(devedge_child_frame), 
         &typeid(view));

      add_document_template(devedge::application_interface::m_ptemplate_devedge);

      m_ptemplate_solution = new ::userbase::single_document_template(
         this, 
         "devedge/frame", 
         &typeid(devedge::solution_document), 
         &typeid(devedge_child_frame), 
         &typeid(devedge::solution_view));

      add_document_template(devedge::application_interface::m_ptemplate_solution);

      m_ptemplateHtmlEdit = new ::userbase::single_document_template(this, "devedge/frame", 
         typeid(devedgeHtmlEditDoc), typeid(devedgeHtmlEditChildFrame), 
         typeid(devedgeHtmlEditView));

      add_document_template(devedge::application_interface::m_ptemplateHtmlEdit);

      devedge::application_interface::m_ptemplateHtml = new ::userbase::single_document_template(this, "devedge/frame", 
         typeid(devedgeHtmlDoc), typeid(devedgeHtmlChildFrame), 
         typeid(devedgeHtmlView));

      add_document_template(devedge::application_interface::m_ptemplateHtml);

      devedge::application_interface::m_ptemplateFront = new ::userbase::single_document_template(this, "devedge/frame", 
         typeid(devedgeFrontDoc), typeid(devedgeFrontChildFrame), 
         typeid(devedgeFrontView));

      add_document_template(devedge::application_interface::m_ptemplateFront);



      KickDevEdgeFront(this);

      gen::command_line line;

      _001ParseCommandLine(line);



      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";
      GetStdFileManagerTemplate()->m_strToolBar = "filemanager_toolbar.xml";

      return true;
   }



   BOOL application::exit_instance()
   {
      return TRUE;
   }


   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      string strExtension = System.file().extension(itema[0].m_strPath);
      if(strExtension.CompareNoCase("ca2solution") == 0)
      {
         m_ptemplate_solution->open_document_file(itema[0].m_strPath);
      }
      else
      {
         string strId = "devedge://" +itema[0].m_strPath;
         m_ppaneview->add_tab(strId, strId);
         m_ppaneview->set_cur_tab_by_id(strId);
      }
   }


   void application::pre_translate_message(gen::signal_object * pobj)
   {
      SCAST_PTR(user::win::message::base, pbase, pobj);
      if(pbase->m_uiMessage == WM_KEYDOWN)
      {
         int i = 1;
         i = i + 1;
      }
      else if(pbase->m_uiMessage == WM_KEYUP)
      {
         int i = 1;
         i = i + 1;
      }
      ::netnode::application::pre_translate_message(pobj);
   }

   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)

   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   ::document * application::_001OpenDocumentFile(var varFile)
   {
      string strExtension = System.file().extension(varFile);
      ::document * pdoc = NULL;
      if(devedge::application_interface::m_ptemplateEdge->get_document_count() == NULL)
      {
         devedge::application_interface::m_ptemplateEdge->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer);
      }
      MainDoc * pmaindoc = NULL;
      if(devedge::application_interface::m_ptemplateEdge->get_document(0) != NULL)
         pmaindoc = dynamic_cast < MainDoc * > (devedge::application_interface::m_ptemplateEdge->get_document(0));
      if(pmaindoc != NULL)
      {
         devedge::pane_view * pview = pmaindoc->get_typed_view < devedge::pane_view > ();
         if(pview != NULL)
         {
            if(strExtension.CompareNoCase("ca2solution") == 0)
            {
               ::userbase::single_document_template * ptemplate = dynamic_cast < ::userbase::single_document_template * >(devedge::application_interface::m_ptemplateEdge);
               if(ptemplate != NULL)
               {
                  if(ptemplate->get_document_count() == NULL)
                  {
                     ptemplate->open_document_file(NULL);
                  }
               }
               pdoc = m_ptemplate_solution->open_document_file(varFile, TRUE, m_puiInitialPlaceHolderContainer);
            }
            else
            {
               pdoc = pview->open_file(varFile);
            }
         }
      }
      return pdoc;
   }

   void application::_001OnFileNew()
   {
      devedge::application_interface::m_ptemplateEdge->open_document_file(NULL, TRUE, System.m_puiInitialPlaceHolderContainer);
   }

   bool application::on_install()
   {
      win::registry::Key key(HKEY_CLASSES_ROOT, ".txt", true);
      key.SetValue(NULL, "txtfile");

      win::registry::Key keyLink3(HKEY_CLASSES_ROOT, "txtfile\\shell", true);
      keyLink3.SetValue(NULL, "open");

      win::registry::Key keyLink2(HKEY_CLASSES_ROOT, "txtfile\\shell\\open", true);
      keyLink2.SetValue(NULL, "&open");

      win::registry::Key keyLink1(HKEY_CLASSES_ROOT, "txtfile\\shell\\open\\command", true);

      string strFormat;
      strFormat.Format("\"%s\" \"%%L\"", System.dir().ca2module("cubeapp.exe"));
      keyLink1.SetValue(NULL, strFormat);

      /*if(VistaTools::IsVista() && VistaTools::IsElevated() == S_OK)
      {
         string strCommand = m_strModulePath;
         strCommand = System.url().url_encode(strCommand);
         DWORD dwSessId;

         HANDLE hProcess = ::GetCurrentProcess();
         DWORD dwId = ::GetProcessId(hProcess);

         ProcessIdToSessionId(dwId, &dwSessId);
         xml::node * pnode = new xml::node;
         pnode->m_strName = "run";
         pnode->add_attr("sessionid", dwSessId);
         pnode->add_attr("command", strCommand);
         machine_event_central().command(pnode);
      }*/
      return true;
   }


} // namespace devedge

