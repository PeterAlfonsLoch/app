#include "StdAfx.h"

namespace user
{

   create_view::view_data::view_data()
   {
      m_pwnd               = NULL;
      m_iExtendOnParent    = 0;
      m_pdoc               = NULL;
   }

   create_view::view_data * create_view::get(id id)
   {
      view_data * pviewdata;
      if(m_viewmap.Lookup(id, pviewdata))
      {
         return pviewdata;
      }
      return NULL;
   }

   int create_view::get_view_count()
   {
      return m_viewmap.get_count();
   }

   create_view::view_data * create_view::ensure(id id)
   {
      create_view::view_data * pviewdata = get(id);
      if(pviewdata != NULL)
         return pviewdata;
      return create(id);
   }

   create_view::view_data * create_view::create(id id)
   {
      create_view::view_data * pviewdata = new view_data;
      pviewdata->m_id = id;
      m_viewmap.set_at(id, pviewdata);
      try
      {
         on_create_view(pviewdata);
      }
      catch(...)
      {
         m_viewmap.remove_key(id);
         delete pviewdata;
         return NULL;
      }
      // pviewdata->m_pwnd == NULL is the criteria to 
      // decide if on_create_view succeeded or failed
      if(pviewdata->m_pwnd == NULL) 
      {
         m_viewmap.remove_key(id);
         delete pviewdata;
         return NULL;
      }
      return pviewdata;
   }

   void create_view::on_create_view(view_data * pviewdata)
   {
      UNREFERENCED_PARAMETER(pviewdata);
   }

   void create_view::on_show_view()
   {
   }

   ::user::interaction * create_view::get_view_uie()
   {
      if(m_pgetview != NULL)
      {
         m_pgetview->get_view_uie();
      }
      return NULL;
   }

   id create_view::get_view_id()
   {
      if(m_pgetview != NULL)
      {
         return m_pgetview->get_view_id();
      }
      return ::ca::system::idEmpty;
   }

   void create_view::hide_all_except(id id)
   {
      view_map::pair * ppair = m_viewmap.PGetFirstAssoc();
      while(ppair != NULL)
      {
         if(id != ppair->m_key)
         {
            if(ppair->m_value->m_pwnd != NULL)
            {
               if(ppair->m_value->m_pwnd->IsWindowVisible())
               {
                  ppair->m_value->m_pwnd->ShowWindow(SW_HIDE);
               }
            }
         }
         ppair = m_viewmap.PGetNextAssoc(ppair);
      }

   }

} // namespace user