#include "framework.h"


namespace filemanager
{


   manager::manager()
   {

   }

   manager::~manager()
   {

   }

   bool manager::FileManagerBrowse(sp(::fs::item) item, ::action::context actioncontext)
   {

      string strOldPath;


      if (m_item.is_set())
      {
         
         strOldPath = m_item->m_strPath;

      }

      try
      {

         m_item = canew(::fs::item(*item));

         if(get_fs_data()->is_link(m_item->m_strPath))
         {
            
            System.os().resolve_link(m_item->m_strPath,m_item->m_strPath);

         }

         OnFileManagerBrowse(::action::source::sync(actioncontext));


      }
      catch (string & str)
      {

         if (str == "uifs:// You have not logged in!")
         {

            Application.simple_message_box(NULL, "You have not logged in! Cannot access your User Intelligent File System - uifs://");

            // assume can resume at least from this exception one time

            m_item = new ::fs::item(strOldPath);

            OnFileManagerBrowse(::action::source::sync(actioncontext));

         }

         return false;

      }

      return false;

   }

   bool manager::FileManagerBrowse(const char * lpcszPath, ::action::context actioncontext)
   {

      FileManagerBrowse(new ::fs::item(lpcszPath), actioncontext);

      return false;

   }

   void manager::FileManagerOneLevelUp(::action::context actioncontext)
   {

      if (get_item().m_strPath.is_empty())
         return;

      string strParent = get_fs_data()->eat_end_level(get_item().m_strPath, 1);

      FileManagerBrowse(strParent, ::action::source::sync(actioncontext));

   }

   void manager::GetActiveViewSelection(::fs::item_array & itema)
   {
      UNREFERENCED_PARAMETER(itema);
   }


   ::fs::item & manager::get_item()
   {
      return *m_item;
   }

   critical_section * manager::GetItemIdListCriticalSection()
   {
      return &m_csItemIdListAbsolute;
   }

   void manager::OnFileManagerBrowse(::action::context actioncontext)
   {

      if (actioncontext.is_user_source())
      {
         
         if (::str::begins(m_item->m_strPath, "uifs://")
            || ::str::begins(m_item->m_strPath, "fs://"))
         {
            data_set("InitialBrowsePath", ::base::system::idEmpty, m_item->m_strPath);
         }
         else
         {

            id idMachine;

#ifdef LINUX
            idMachine = "Linux";
#elif defined(WINDOWSEX)
            idMachine = "Windows Desktop";
#endif

            data_set("InitialBrowsePath", ::base::system::idEmpty, "machinefs://");
            data_set("InitialBrowsePath", idMachine, m_item->m_strPath);

         }

      }

   }

   void manager::OpenSelectionProperties()
   {
   }

   void manager::FileManagerSaveAs(sp(::user::object) pdocument)
   {
      get_filemanager_data()->m_pdocumentSave = pdocument;
   }

   void manager::FileManagerSaveOK()
   {
   }

   void manager::FileManagerSaveCancel()
   {
   }

   ::fs::data * manager::get_fs_data()
   {
      return NULL;
   }


   string manager::calc_key(::database::id & idSection, ::database::id & id, ::database::id & idIndex)
   {
      string str;
      str += idSection.get_id().str();
      str += ".";
      str += id.get_id().str();
      str += ".";
      str += idIndex.get_id().str();
      return str;
   }



} // namespace filemanager




