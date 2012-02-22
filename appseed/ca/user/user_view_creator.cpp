#include "StdAfx.h"


namespace user
{


   view_creator_data::view_creator_data()
   {
      m_pwnd               = NULL;
      m_iExtendOnParent    = 0;
      m_pdoc               = NULL;
      m_pviewdata          = NULL;
      m_pholder            = NULL;
   }

   view_creator_data * view_creator::get(id id)
   {
      ::user::view_creator_data * pcreatordata;
      if(m_viewmap.Lookup(id, pcreatordata))
      {
         return pcreatordata;
      }
      return NULL;
   }


   view_creator::view_creator()
   {
      m_pviewcontainer           = NULL;
   }

   view_creator::~view_creator()
   {
   }

   count view_creator::get_view_count()
   {
      return m_viewmap.get_count();
   }

   view_creator_data * view_creator::ensure(id id)
   {
      view_creator_data * pcreatordata = get(id);
      if(pcreatordata != NULL)
         return pcreatordata;
      return create(id);
   }

   view_creator_data * view_creator::allocate(id id)
   {
      view_creator_data * pcreatordata = new ::user::view_creator_data;
      pcreatordata->m_id = id;
      m_viewmap.set_at(id, pcreatordata);
      return pcreatordata;
   }

   view_creator_data * view_creator::create(id id)
   {
      view_creator_data * pcreatordata = allocate(id);
      if(m_pviewcontainer != NULL)
      {
         try
         {
            m_pviewcontainer->on_new_view_creator_data(pcreatordata);
         }
         catch(...)
         {
         }
      }
      if(m_pviewcontainer != this)
      {
         try
         {
            on_new_view_creator_data(pcreatordata);
         }
         catch(...)
         {
         }
      }
      try
      {
         on_create_view(pcreatordata);
      }
      catch(...)
      {
      }
      return pcreatordata;
   }

   void view_creator::on_create_view(::user::view_creator_data * pcreatordata)
   {
      UNREFERENCED_PARAMETER(pcreatordata);
   }

   void view_creator::on_show_view()
   {
   }

   ::user::interaction * view_creator::get_view()
   {
      if(m_pviewcontainer != NULL)
      {
         m_pviewcontainer->get_view();
      }
      return NULL;
   }

   id view_creator::get_view_id()
   {
      if(m_pviewcontainer != NULL)
      {
         return m_pviewcontainer->get_view_id();
      }
      return ::radix::system::idEmpty;
   }

   void view_creator::hide_all_except(id id)
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

   void view_creator::on_new_view_creator_data(::user::view_creator_data * pcreatordata)
   {
      UNREFERENCED_PARAMETER(pcreatordata);
   }

   void view_creator::on_update(::document * pdocument, ::view * pSender, LPARAM lHint, ::radix::object* pHint)
   {
      POSITION pos = m_viewmap.get_start_position();
      ::user::view_creator_data * pcreatordata;
      id id;
      while(pos != NULL)
      {
         m_viewmap.get_next_assoc(pos, id, pcreatordata);
         if(pcreatordata->m_pdoc != NULL && pcreatordata->m_pdoc != pdocument && (pSender == NULL || pSender->get_document() != pcreatordata->m_pdoc))
         {
            pcreatordata->m_pdoc->update_all_views(pSender, lHint, pHint);
         }
      }
   }


} // namespace user

