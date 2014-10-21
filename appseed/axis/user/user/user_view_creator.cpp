#include "framework.h" // from "axis/user/user.h"


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

   ::user::interaction * view_creator_data::get_wnd()
   {
      if(m_pwnd != NULL)
         return m_pwnd;
      try
      {
         if(m_pholder != NULL && m_pholder->m_uiptraHold.get_count() == 1)
            return m_pholder->m_uiptraHold[0];
      }
      catch(...)
      {
      }
      return NULL;
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

   ::count view_creator::get_view_count()
   {
      return m_viewmap.get_count();
   }

   view_creator_data * view_creator::ensure_impact(id id, LPCRECT lpcrectCreate)
   {
      view_creator_data * pcreatordata = get(id);
      if(pcreatordata != NULL)
         return pcreatordata;
      return create_impact(id,lpcrectCreate);
   }

   view_creator_data * view_creator::allocate(id id)
   {
      view_creator_data * pcreatordata = new ::user::view_creator_data;
      pcreatordata->m_id = id;
      m_viewmap.set_at(id, pcreatordata);
      return pcreatordata;
   }

   view_creator_data * view_creator::create_impact(id id,LPCRECT lpcrectCreate)
   {
      view_creator_data * pcreatordata = allocate(id);
      pcreatordata->m_rectCreate = *lpcrectCreate;
      if(m_pviewcontainer != NULL)
      {
         try
         {
            m_pviewcontainer->on_new_view_creator_data(pcreatordata);
         }
         catch(::exit_exception & e)
         {

            throw e;

         }
         catch(::exception::exception & e)
         {

            if(!Application.on_run_exception(e))
               throw exit_exception(get_app());

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
         catch(::exit_exception & e)
         {

            throw e;

         }
         catch(::exception::exception & e)
         {

            if(!Application.on_run_exception(e))
               throw exit_exception(get_app());

         }
         catch(...)
         {
         }
      }
      try
      {
         on_create_view(pcreatordata);
      }
      catch(create_exception & e)
      {
         if(e.m_id == id)
         {
            delete pcreatordata;
            return NULL;
         }
         throw e;
      }
      catch(::exit_exception & e)
      {

         throw e;

      }
      catch(::exception::exception & e)
      {

         if(!Application.on_run_exception(e))
            throw exit_exception(get_app());

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
      //return ::axis::system::idEmpty;
      return id();
   }

   void view_creator::hide_all_except(id id)
   {
      view_map::pair * ppair = m_viewmap.PGetFirstAssoc();
      while(ppair != NULL)
      {
         if(id != ppair->m_element1)
         {
            try
            {
               if(ppair->m_element2->m_pholder != NULL)
               {
                  ppair->m_element2->m_pholder->ShowWindow(SW_HIDE);
               }
               else if(ppair->m_element2->m_pwnd != NULL)
               {
                  ppair->m_element2->m_pwnd->ShowWindow(SW_HIDE);
               }
            }
            catch(...)
            {

            }

         }

         ppair = m_viewmap.PGetNextAssoc(ppair);

      }

   }


   void view_creator::on_new_view_creator_data(::user::view_creator_data * pcreatordata)
   {

      UNREFERENCED_PARAMETER(pcreatordata);

   }


   void view_creator::on_update(::user::document * pdocument, ::user::impact * pSender, LPARAM lHint, object* pHint)
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



