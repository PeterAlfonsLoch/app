#include "framework.h"


namespace usermail
{


   list_interface::data::data(sp(::aura::application) papp) :
      element(papp),
      ::user::list_data(papp)
   {
   }



   list_interface::list_interface(sp(::aura::application) papp) :
      element(papp),
      
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
      ::user::list_column column;
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


   void list_interface::data::_001GetItemText(::user::list_item * pitem)
   {
      single_lock slDataset(&m_plist->m_paccount->m_pop3.m_csDataset, TRUE);
      string strId;
      strId = m_straId[pitem->m_iItem];
      if(pitem->m_iSubItem == 0)
      {
         pitem->m_strText = m_plist->m_paccount->m_pop3.m_pdataset->query_item("select sender from inbox where id = '" + strId + "'");
      }
      else if(pitem->m_iSubItem == 1)
      {
         pitem->m_strText = m_plist->m_paccount->m_pop3.m_pdataset->query_item("select subject from inbox where id = '" + strId + "'");
      }
      else if(pitem->m_iSubItem == 2)
      {
         pitem->m_strText = m_plist->m_paccount->m_pop3.m_pdataset->query_item("select sentdatetime from inbox where id = '" + strId + "'");
      }
      if(m_plist->m_paccount->m_pop3.m_pdataset->num_rows() == 1)
      {
         pitem->m_strText = m_plist->m_paccount->m_pop3.m_pdataset->FieldValueAt(0);
      }
      else
      {
         pitem->m_bOk = false;
         return;
      }
      pitem->m_bOk = true;
      return;
   }

   int_ptr list_interface::data::_001GetItemCount()
   {
      return m_straId.get_size();
   }

   void list_interface::data::update()
   {
      if(m_plist->m_paccount == NULL)
         return;
      single_lock slDataset(&m_plist->m_paccount->m_pop3.m_csDataset, TRUE);
      m_straId.remove_all();
      sp(::sqlite::set) pdataset = m_plist->m_paccount->m_pop3.m_pdataset;
      pdataset->query_items(m_straId, "select id from inbox");
   }

   bool list_interface::_001OnUpdateItemCount(uint32_t dwFlags)
   {
      m_pdata->update();
      return ::user::list::_001OnUpdateItemCount(dwFlags);
   }


} // namespace mail


