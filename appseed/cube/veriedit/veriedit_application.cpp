#include "StdAfx.h"

void KickNetNodeThread();

namespace veriedit 
{

   application::application()
   {
      m_ppaneview = NULL;
   }

   void application::construct()
   {
      //m_pscriptmanager     = NULL;
      m_strAppName         = "veriedit";
      m_strBaseSupportId   = "votagus_ca2_veriedit";
      m_strInstallToken    = "veriedit";
      //m_ppaneview          = NULL;
   }

   application::~application(void)
   {
   }

   bool application::initialize_instance()
   {
      System.factory().creatable_small < main_document > ();
      System.factory().creatable_small < main_frame > ();
      System.factory().creatable_small < pane_view > ();

      System.factory().creatable_small < document > ();
      System.factory().creatable_small < frame > ();
      System.factory().creatable_small < edit_view > ();

      if(!ca84::application::initialize_instance())
         return false;

      m_ptemplateMain = 
         new ::userbase::single_document_template(
               get_app(),
               "veriedit/main_frame",
               typeid(main_document),
               typeid(main_frame),
               typeid(pane_view));

      add_document_template(m_ptemplateMain);

      m_ptemplateEdit = 
         new ::userbase::multiple_document_template(
               get_app(),
               "veriedit/frame",
               typeid(document),
               typeid(frame),
               typeid(edit_view));

      add_document_template(m_ptemplateEdit);

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";
      GetStdFileManagerTemplate()->m_strToolBar = "filemanager_toolbar.xml";
      GetStdFileManagerTemplate()->m_strToolBarSave = "filemanager_save_as_toolbar.xml";

      return true;
   }



   BOOL application::exit_instance()
   {
      return TRUE;
   }


   void application::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      string strId = "veriedit://" + itema[0].m_strPath;
      if(m_ppaneview == NULL)
      {
         m_ptemplateMain->open_document_file(NULL, true, m_puiInitialPlaceHolderContainer);
      }
      m_ppaneview->add_tab(strId, strId);
      m_ppaneview->set_cur_tab_by_id(strId);
   }


   bool application::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)

   {
      return gen::application::_001OnCmdMsg(pcmdmsg);
   }

   ::document * application::_001OpenDocumentFile(var varFile)
   {
      string strId = "veriedit://" + string(varFile);
      if(m_ppaneview == NULL)
      {
         m_ptemplateMain->open_document_file(NULL, true, m_puiInitialPlaceHolderContainer);
      }
      m_ppaneview->add_tab(strId, strId);
      m_ppaneview->set_cur_tab_by_id(strId);
      return m_ppaneview->get_veriedit_document(strId);
   }

   void application::_001OnFileNew()
   {
      string strPath;
      string strFormatTime;
      strFormatTime = System.datetime().international().get_gmt_date_time();
      strFormatTime.replace(":", "-");
      strPath = System.dir().path(get_file_manager_initial_browse_path(), strFormatTime + ".txt");
      if(!System.file().exists(strPath))
      {
         System.file().put_contents(strPath, "");
      }
      string strId = "veriedit://" + strPath;
      if(m_ppaneview == NULL)
      {
         m_ptemplateMain->open_document_file(NULL, true, m_puiInitialPlaceHolderContainer);
      }
      m_ppaneview->add_tab(strId, strId);
      m_ppaneview->set_cur_tab_by_id(strId);
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

      return true;
   }


} // namespace devedge

