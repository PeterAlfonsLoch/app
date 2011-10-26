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
      connect_command("file_new", &::ex2::application::_001OnFileNew);
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

      if(!cube2::application::initialize_instance())
         return false;

      m_dataid = "ca2_fontopus_votagus::veriedit::application";

      m_ptemplateMain = 
         new ::userbase::single_document_template(
               this,
               "veriedit/main_frame",
               ::ca::get_type_info < main_document > (),
               ::ca::get_type_info < main_frame > (),
               ::ca::get_type_info < pane_view > ());

//      add_document_template(m_ptemplateMain);

      m_ptemplateEdit = 
         new ::userbase::multiple_document_template(
               this,
               "veriedit/frame",
               ::ca::get_type_info < document > (),
               ::ca::get_type_info < frame > (),
               ::ca::get_type_info < edit_view > ());

      Bergedge.add_document_template(m_ptemplateEdit);

      //add_document_template(m_ptemplateEdit);

      GetStdFileManagerTemplate()->m_strLevelUp = "levelup";
      GetStdFileManagerTemplate()->m_strToolBar = "filemanager_toolbar.xml";
      GetStdFileManagerTemplate()->m_strToolBarSave = "filemanager_save_as_toolbar.xml";

      GetFsManagerTemplate()->m_strLevelUp = "levelup";
      GetFsManagerTemplate()->m_strToolBar = "filemanager_toolbar.xml";
      GetFsManagerTemplate()->m_strToolBarSave = "filemanager_save_as_toolbar.xml";

      return true;
   }



   void application::on_request(::ca::create_context * pcreatecontext)
   {

      if(m_ppaneview == NULL)
      {
         ::document * pdoc = m_ptemplateMain->open_document_file(pcreatecontext);
         if(pdoc != NULL)
         {
            ::view * pview = pdoc->get_view();
            if(pview != NULL)
            {
               ::simple_frame_window * pframe = dynamic_cast < simple_frame_window * > (pview->GetParentFrame());
               if(pframe != NULL)
               {
                  ::bergedge::pane_view * ppaneview = pframe->GetTypedParent < ::bergedge::pane_view > ();
                  if(ppaneview != NULL)
                  {
                     ::user::view_creator_data * pcreatordata = ppaneview->get("app:veriedit");
                     if(pcreatordata != NULL)
                     {
                        //pcreatordata->m_iExtendOnParent = 0;
                     }
                  }
               }
            }
         }

      }

      string strId;
      if(pcreatecontext->m_spCommandLine->m_varQuery["command"] == "new_file")
      {
         string strPath;
         string strFormatTime;
         strFormatTime = System.datetime().international().get_gmt_date_time();
         strFormatTime.replace(":", "-");
         strPath = System.dir().path(get_file_manager_initial_browse_path(), strFormatTime + ".txt");
         if(!System.file().exists(strPath))
         {
            Application.file().put_contents(strPath, "");
         }
         strId = "veriedit://" + strPath;
      }
      else if(pcreatecontext->m_spCommandLine->m_varFile.get_string().has_char())
      {
         strId = "veriedit://" + string(pcreatecontext->m_spCommandLine->m_varFile);
      }

      if(strId.has_char())
      {
         m_ppaneview->add_tab(strId, strId);
         m_ppaneview->set_cur_tab_by_id(strId);
         m_ppaneview->get_veriedit_document(strId);
      }
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
      strFormat.Format("\"%s\" \"%%L\"", System.dir().ca2module("ca2app.exe"));
      keyLink1.SetValue(NULL, strFormat);

      {
         win::registry::Key key(HKEY_CLASSES_ROOT, ".pac", true);
         key.SetValue(NULL, "txtfile");

/*         win::registry::Key keyLink3(HKEY_CLASSES_ROOT, "txtfile\\shell", true);
         keyLink3.SetValue(NULL, "open");

         win::registry::Key keyLink2(HKEY_CLASSES_ROOT, "txtfile\\shell\\open", true);
         keyLink2.SetValue(NULL, "&open");

         win::registry::Key keyLink1(HKEY_CLASSES_ROOT, "txtfile\\shell\\open\\command", true);

         string strFormat;
         strFormat.Format("\"%s\" \"%%L\"", System.dir().ca2module("ca2app.exe"));
         keyLink1.SetValue(NULL, strFormat);*/
      }

      return true;
   }


} // namespace devedge

