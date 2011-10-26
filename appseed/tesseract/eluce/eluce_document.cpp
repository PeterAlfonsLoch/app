#include "StdAfx.h"
#include "include/FreeImage.h"


namespace eluce
{

   document::document(::ca::application * papp) :
      ca(papp),
      ::ca::data_container(papp),
      ::document(papp),
      ::userbase::document(papp),
      m_spdib(papp)
   {
      connect_command("go_to_previous", &document::_001OnGoToPrevious);
      connect_command("go_to_next", &document::_001OnGoToNext);
      connect_command("file_new_paste", &document::_001OnFileNewPaste);
      connect_update_cmd_ui("file_save_as", &document::_001OnUpdateFileSaveAs);
      connect_command("file_save_as", &document::_001OnFileSaveAs);
   }

   BOOL document::on_new_document()
   {
      if (!::userbase::document::on_new_document())
         return FALSE;

      string strFile;

      if(data_get("last_open_document", strFile))
      {
         if(on_open_document(strFile))
            return TRUE;
      }
      else
      {
         _001OnGoToNext(NULL);
      }

      update_all_views(NULL, 0);

      return TRUE;
   }

   document::~document()
   {
   }



   #ifdef _DEBUG
   void document::assert_valid() const
   {
      ::userbase::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::userbase::document::dump(dumpcontext);
   }
   #endif //_DEBUG


   bool document::on_open_document(var varFile)
   {

      if(!m_spdib.load_from_file(varFile))
         return false;

      m_bNew = false;

//      if(!::userbase::document::on_open_document(varFile))
  //       return false;

      set_path_name(varFile.get_string());

      update_all_views(NULL);

      data_set("last_open_document", varFile.get_string());

      return true;
   }


   BOOL document::on_save_document(const char * lpszPathName)
   {
      if(!m_spdib.save_to_file(lpszPathName))
         return false;


      return TRUE;
   }



   void document::_001OnGoToPrevious(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      string strDir = System.dir().name(get_path_name());
      stringa stra;
      Application.fs()->ls(strDir, &stra, NULL);
      stra.QuickSort();
      int iPrevious = stra.find_first_ci(get_path_name());
      int iPreviousPrevious = iPrevious;
restart:
      if(iPrevious < 0)
         iPrevious = stra.get_upper_bound();
      else
         iPrevious = iPrevious - 1;
      if(iPrevious < 0)
         iPrevious = stra.get_upper_bound();
      if(iPrevious > stra.get_upper_bound())
         return;
      if(!(gen::str::ends_ci(stra[iPrevious], ".jpg")
      || gen::str::ends_ci(stra[iPrevious], ".png"))
      || !on_open_document(stra[iPrevious]))
      {
         if(iPrevious != iPreviousPrevious)
         {
            goto restart;
         }
      }
   }

   void document::_001OnGoToNext(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      string strDir = System.dir().name(get_path_name());
      stringa stra;
      Application.fs()->ls(strDir, &stra, NULL);
      stra.QuickSort();
      int iNext = stra.find_first_ci(get_path_name());
      int iPreviousNext = iNext;
      if(iPreviousNext < 0)
         iPreviousNext = 0;
   restart:
      if(iNext < 0)
         iNext = 0;
      else
         iNext = iNext + 1;
      if(iNext > stra.get_upper_bound())
         iNext = 0;
      if(iNext < 0)
         return;
      if(!(gen::str::ends_ci(stra[iNext], ".jpg")
      || gen::str::ends_ci(stra[iNext], ".png"))
      || !on_open_document(stra[iNext]))
      {
         if(iNext != iPreviousNext)
         {
            goto restart;
         }
      }
   }

   void document::_001OnFileNewPaste(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      if (!::userbase::document::on_new_document())
         return;
      System.copydesk().desk_to_dib(m_spdib);
      m_bNew = false;
   }

   void document::_001OnUpdateFileSaveAs(gen::signal_object * pobj)
   {
      SCAST_PTR(base_cmd_ui, pcmdui, pobj)
      pcmdui->m_pcmdui->Enable(TRUE);
   }

   void document::_001OnFileSaveAs(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      Application.::eluce::application::m_ppaneview->set_cur_tab_by_id("file_manager");
      Application.::eluce::application::m_ppaneview->m_pfilemanagerdoc->FileManagerSaveAs(this);
   }


} // namespace eluce
