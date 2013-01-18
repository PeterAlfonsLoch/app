#include "framework.h"


FileManagerSaveAsView::FileManagerSaveAsView(::ca::application * papp) :
   ca(papp),
   ::userbase::edit_plain_text_view(papp),
   ::user::interaction(papp),
   ::userbase::view(papp),
   ::user::scroll_view(papp)
{

   m_bVoidSync = false;

}

void FileManagerSaveAsView::on_update(::view * pSender, LPARAM lHint, ::radix::object* phint)
{
   FileManagerViewInterface::on_update(pSender, lHint, phint);
   if(phint != NULL)
   {
      if(base < FileManagerViewUpdateHint >::bases(phint))
      {
         FileManagerViewUpdateHint * puh = (FileManagerViewUpdateHint *) phint;
         if(puh->m_pview == this &&
            puh->is_type_of(FileManagerViewUpdateHint::TypeInitialize))
         {
//            GetFileManager() = puh->GetFileManager();
/*            m_pserverNext = simpledb::AppGet()->GetDataServer();
            AddClient(this);
            SetDataInterface(&m_datainterface);
            AddClient(&m_datainterface);
            string str;
            str.Format("SimpleFileListView(%d,%d)", GetFileManager()->get_filemanager_data()->m_iTemplate, GetFileManager()->get_filemanager_data()->m_iDocument);
            if(GetFileManager()->get_filemanager_data()->m_bTransparentBackground)
            {
               ::user::list::m_etranslucency = ::user::list::TranslucencyPresent;
            }
            DISetSection(str);
            _001UpdateColumns();*/
         }
         else if(puh->is_type_of(FileManagerViewUpdateHint::TypePreSynchronize))
         {
            //_017PreSynchronize();
         }
         else if(puh->is_type_of(FileManagerViewUpdateHint::TypeSynchronize))
         {
            _017Synchronize();
         }
         else if(puh->is_type_of(FileManagerViewUpdateHint::TypeFilter))
         {
            /*if(puh->m_wstrFilter.is_empty())
            {
               FilterClose();
            }
            else
            {
               FilterBegin();
               Filter1(puh->m_wstrFilter);
               FilterApply();
            }*/
         }
         else if(base < form_update_hint >::bases(phint))
         {
            /*form_update_hint * puh = dynamic_cast<form_update_hint * > (phint);
            if(puh->m_etype == form_update_hint::type_after_browse)
            {
               if(puh->m_strForm == "filemanager\\replace_name_in_file_system.xhtml")
               {
                  html::elemental * pelemental = dynamic_cast < html::elemental * > (puh->m_pformview->get_document()->m_document.get_element_by_name("encontrar"));
                  html::impl::input_text * pinput = dynamic_cast < html::impl::input_text * > (pelemental->m_pimpl);
                  text_interface * ptext = dynamic_cast < text_interface * > (pinput->m_pedit);
                  Range range;
                  _001GetSelection(range);
                  if(range.get_item_count() > 0)
                  {
                     ptext->_001SetText(m_itema.get_item(range.ItemAt(0).GetLBound()).m_strName);
                  }
               }
            }
            file_manager_form_update_hint * pmanageruh = dynamic_cast<file_manager_form_update_hint * > (phint);
            if(pmanageruh != NULL)
            {
               if(!pmanageruh->m_strFind.is_empty())
               {
                  System.file().replace(m_strPath, pmanageruh->m_strFind, pmanageruh->m_strReplace);
                  _017UpdateList();
               }
            }*/
         }
      }
   }
}


void FileManagerSaveAsView::_017Synchronize()
{
   if(m_bVoidSync)
      return;
   string strText;
   _001GetText(strText);
   if(strText != System.file().title_(GetFileManager()->get_filemanager_data()->m_pmanager->m_strTopic))
   {
      _001SetText(System.file().title_(GetFileManager()->get_filemanager_data()->m_pmanager->m_strTopic));
   }
}

void FileManagerSaveAsView::_001OnAfterChangeText()
{

   string str;

   _001GetText(str);

   if(Application.dir().is(str))
   {
      GetFileManager()->FileManagerBrowse(str);
   }
   else if(str.find("/") >= 0 || str.find("\\") >= 0)
   {
      string strName = str;
      while(true)
      {
         strName = System.dir().name(strName);
         if(Application.dir().is(strName))
         {
            if(!System.file().path().is_equal(GetFileManager()->get_item().m_strPath, strName))
            {
               GetFileManager()->FileManagerBrowse(strName);
            }
            break;
         }
         if(strName.is_empty())
            break;
      }
   }

   GetFileManager()->m_strTopic = str;

}


