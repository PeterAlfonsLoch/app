#include "StdAfx.h"

namespace veiev
{

   list_interface::list_interface(::ca::application * papp) :
      ca(papp),
      ::user::scroll_view(papp),
      ::user::list(papp)
   {

      m_pprofile        = NULL;
      m_dataid          = "mail::list_interface";
      m_pdata           = new data(papp);
      m_pdata->m_plist  = this;
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


   list_interface::data::data(::ca::application * papp) :
      ca(papp),
      ::ca::data(papp),
      ::user::list_data(papp)
   {
       m_iCachePage        = -1;
       m_iCachePageSize    = 100;
   }

   list_interface::data::~data()
   {
   }

   bool list_interface::data::get_record(int iItem, var & var)
   {
      int iLoBound = m_iCachePage * m_iCachePageSize;
      int iHiBound = min(iLoBound + m_iCachePageSize - 1, iLoBound + m_varCache.vara().get_size() - 1);
      if(iItem < iLoBound || iItem > iHiBound)
      {
         if(iItem < 0)
            return false;
         if(iItem >= _001GetItemCount())
            return false;
         m_iCachePage = iItem / m_iCachePageSize;
         m_varCache = App(m_plist->get_app()).db().veiev_post().get_page(m_iCachePage, m_iCachePageSize);
         iLoBound = m_iCachePage * m_iCachePageSize;
         iHiBound = min(iLoBound + m_iCachePageSize - 1, iLoBound + m_varCache.vara().get_size() - 1);
         if(iItem < iLoBound || iItem > iHiBound)
         {
            return false;
         }
      }
      int iPageItem = iItem - iLoBound;
      var = m_varCache.vara()[iPageItem];
      return true;
   }

   void list_interface::data::_001GetItemText(::user::list_item * pitem)
   {
      single_lock slDataset(App(m_plist->get_app()).db().GetImplCriticalSection(), TRUE);
      class var var;
      if(!get_record(pitem->m_iItem, var))
         return_(pitem->m_bOk, false);
      if(pitem->m_iSubItem < 0)
         return_(pitem->m_bOk, false);
      if(pitem->m_iSubItem >= var.propset().m_propertya.get_size())
         return_(pitem->m_bOk, false);
      pitem->m_strText = var.propset().m_propertya[pitem->m_iSubItem];
      pitem->m_bOk = true;
   }

   INT_PTR list_interface::data::_001GetItemCount()
   {
      return (INT_PTR) m_iMessageCount;
   }

   void list_interface::data::update()
   {
      m_varCache.vara().remove_all();
      m_iMessageCount = App(m_plist->get_app()).db().veiev_post().get_count();
   }

   bool list_interface::_001OnUpdateItemCount(DWORD dwFlags)
   {
      m_pdata->update();
      return ::user::list::_001OnUpdateItemCount(dwFlags);
   }

   var list_interface::get_selected_message()
   {
      Range range;
      _001GetSelection(range);
      if(range.get_item_count() <= 0)
         return false;
      int iItem = 0;
      if(range.ItemAt(0).GetLBound() > 0)
         iItem = range.ItemAt(0).GetLBound();
      class var var;
      m_pdata->get_record(iItem, var);
      return var;
   }

} // namespace veiev