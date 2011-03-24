#include "StdAfx.h"

namespace mail
{

   list_interface::data::data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp),
      ::user::list_data(papp)
   {
   }



   list_interface::list_interface(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::list(papp)
   {
      m_paccount= NULL;
      m_dataid = "mail::list_interface";
      m_pdata = new data(papp);
      m_pdata->m_plist = this;
      SetDataInterface(m_pdata);

      
   }

   void list_interface::_001InsertColumns()
   {
      Column column;
      column.m_iWidth = 200;
      column.m_iSubItem = 0;

      _001InsertColumn(column);
      column.m_iWidth = 300;
      column.m_iSubItem = 1;

      _001InsertColumn(column);
      column.m_iWidth = 100;
      column.m_iSubItem = 2;

      _001InsertColumn(column);
   }


   list_interface::~list_interface()
   {
      delete m_pdata;
   }


   bool list_interface::data::_001GetItemText(
      ::user::list * plist,
      string &str,
      INT_PTR iItem,
      INT_PTR iSubItem, 
      INT_PTR iListItem)
   {
      UNREFERENCED_PARAMETER(plist);
      UNREFERENCED_PARAMETER(iListItem);
      CSingleLock slDataset(&m_plist->m_paccount->m_pop3.m_csDataset, TRUE);
      string strId;
      strId = m_straId[iItem];
      if(iSubItem == 0)
      {
         m_plist->m_paccount->m_pop3.m_pdataset->query("select sender from inbox where id = '" + strId + "'");
      }
      else if(iSubItem == 1)
      {
         m_plist->m_paccount->m_pop3.m_pdataset->query("select subject from inbox where id = '" + strId + "'");
      }
      else if(iSubItem == 2)
      {
         m_plist->m_paccount->m_pop3.m_pdataset->query("select sentdatetime from inbox where id = '" + strId + "'");
      }
      if(m_plist->m_paccount->m_pop3.m_pdataset->num_rows() == 1)
      {
         str = m_plist->m_paccount->m_pop3.m_pdataset->FieldValueAt(0);
         return true;
      }
      else
      {
         return false;
      }
   }

   INT_PTR list_interface::data::_001GetItemCount()
   {
      return m_straId.get_size();
   }

   void list_interface::data::update()
   {
      if(m_plist->m_paccount == NULL)
         return;
      CSingleLock slDataset(&m_plist->m_paccount->m_pop3.m_csDataset, TRUE);
      m_straId.remove_all();
      ::sqlite::set * pdataset = m_plist->m_paccount->m_pop3.m_pdataset;
      pdataset->query_items(m_straId, "select id from inbox");
   }

   bool list_interface::_001OnUpdateItemCount(DWORD dwFlags)
   {
      m_pdata->update();
      return ::user::list::_001OnUpdateItemCount(dwFlags);
   }

} // namespace mail