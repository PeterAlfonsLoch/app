//#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   view_creator_data::view_creator_data()
   {

      m_pwnd               = NULL;
      m_iExtendOnParent    = 0;
      m_pdoc               = NULL;
      m_pviewdata          = NULL;
      m_pholder            = NULL;
      m_bOk                = true;

   }


   ::user::interaction * view_creator_data::get_wnd()
   {

      if(m_pwnd != NULL)
         return m_pwnd;

      try
      {

         if(m_pholder != NULL && m_pholder->m_uiptraChild.get_count() == 1)
            return m_pholder->m_uiptraChild[0];

      }
      catch(...)
      {

      }

      return NULL;

   }


   view_creator_data * view_creator::get(id id)
   {
      ::user::view_creator_data * pcreatordata;
      if(m_viewmap.lookup(id, pcreatordata))
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
      for (auto & p : m_viewmap)
      {
         delete p.m_element2;
      }
   }

   ::count view_creator::get_view_count()
   {
      return m_viewmap.get_count();
   }


   view_creator_data * view_creator::get_impact(id id, LPCRECT lpcrectCreate)
   {

      view_creator_data * pcreatordata = get(id);

      if (pcreatordata != NULL)
      {

         return pcreatordata;

      }

      return create_impact(id,lpcrectCreate);

   }


   view_creator_data * view_creator::allocate_creator_data(id id)
   {

      view_creator_data * pcreatordata = new ::user::view_creator_data;

      pcreatordata->m_id = id;

      return pcreatordata;

   }


   view_creator_data * view_creator::allocate_creator_data(id id, LPCRECT lpcrectCreate)
   {

      view_creator_data * pcreatordata = allocate_creator_data(id);

      pcreatordata->m_rectCreate = *lpcrectCreate;

      if (m_pviewcontainer != NULL)
      {

         try
         {

            m_pviewcontainer->on_prepare_view_creator_data(pcreatordata);

         }
         catch (::exit_exception & e)
         {

            throw e;

         }
         catch (::exception::exception & e)
         {

            if (!Application.on_run_exception(e))
            {

               throw exit_exception(get_app());

            }

         }
         catch (...)
         {

         }

      }

      if (m_pviewcontainer != this)
      {

         try
         {

            on_prepare_view_creator_data(pcreatordata);

         }
         catch (::exit_exception & e)
         {

            throw e;

         }
         catch (::exception::exception & e)
         {

            if (!Application.on_run_exception(e))
            {

               throw exit_exception(get_app());

            }

         }
         catch (...)
         {

         }

      }

      return pcreatordata;

   }


   view_creator_data * view_creator::create_impact(id idInitialize,LPCRECT lpcrectCreate)
   {

      view_creator_data * pcreatordata = allocate_creator_data(idInitialize, lpcrectCreate);

      try
      {

         on_create_view(pcreatordata);

      }
      catch(create_exception & e)
      {

         if(e.m_id == idInitialize)
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

         if (!Application.on_run_exception(e))
         {
         
            throw exit_exception(get_app());

         }

      }
      catch(...)
      {

      }
      
      if (!pcreatordata->m_bOk)
      {

         delete pcreatordata;

         return NULL;

      }

      if (m_pviewcontainer != NULL)
      {

         try
         {

            m_pviewcontainer->on_after_create_view_creator_data(pcreatordata);

         }
         catch (::exit_exception & e)
         {

            throw e;

         }
         catch (::exception::exception & e)
         {

            if (!Application.on_run_exception(e))
            {

               throw exit_exception(get_app());

            }

         }
         catch (...)
         {

         }

      }

      if (m_pviewcontainer != this)
      {

         try
         {

            on_after_create_view_creator_data(pcreatordata);

         }
         catch (::exit_exception & e)
         {

            throw e;

         }
         catch (::exception::exception & e)
         {

            if (!Application.on_run_exception(e))
            {

               throw exit_exception(get_app());

            }

         }
         catch (...)
         {

         }

      }

      return on_after_create_impact(pcreatordata);

   }


   view_creator_data * view_creator::on_after_create_impact(view_creator_data * pcreatordata)
   {

      m_viewmap.set_at(pcreatordata->m_id, pcreatordata);

      if (pcreatordata->m_pholder->m_uiptraChild.get_count() > 0)
      {

         return pcreatordata;

      }

      try
      {

         Application.on_create_view(pcreatordata);

      }
      catch (create_exception & e)
      {

         if (e.m_id == pcreatordata->m_id)
         {

            delete pcreatordata;

            return NULL;

         }

         throw e;

      }
      catch (::exit_exception & e)
      {

         throw e;

      }
      catch (::exception::exception & e)
      {

         if (!Application.on_run_exception(e))
         {

            throw exit_exception(get_app());

         }

      }
      catch (...)
      {

      }

      return pcreatordata;

   }


   view_creator_data * view_creator::create_impact(id id, LPCRECT lpcrectCreate, ::user::frame_window * pframewindow)
   {

      view_creator_data * pcreatordata = allocate_creator_data(id, lpcrectCreate);

      pcreatordata->m_pwnd = pframewindow;

      pcreatordata->m_pdoc = pframewindow->GetActiveDocument();

      pcreatordata->m_bOk = true;

      return on_after_create_impact(pcreatordata);

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
      //return ::aura::system::idEmpty;
      return id();
   }

   void view_creator::hide_all_except(const id_array & ida)
   {
      
      for(auto & item : m_viewmap)
      {
         
         if(!ida.contains(item.m_element1))
         {
            try
            {
               if(item.m_element2->m_pholder != NULL)
               {
                  item.m_element2->m_pholder->ShowWindow(SW_HIDE);
               }
               else if(item.m_element2->m_pwnd != NULL)
               {
                  item.m_element2->m_pwnd->ShowWindow(SW_HIDE);
               }
            }
            catch(...)
            {

            }

         }

      }

   }

   //void view_creator::hide_all_except(id id)
   //{
   //   array<id> ida;
   //   ida.add(id);
   //   hide_all_except(id);

   //}

   bool view_creator::on_prepare_view_creator_data(::user::view_creator_data * pcreatordata)
   {

      UNREFERENCED_PARAMETER(pcreatordata);

      return false;

   }


   bool view_creator::on_after_create_view_creator_data(::user::view_creator_data * pcreatordata)
   {

      UNREFERENCED_PARAMETER(pcreatordata);

      return false;

   }


   void view_creator::on_update(::user::document * pdocument, ::user::impact * pSender, LPARAM lHint, object* pHint)
   {

      auto pos = m_viewmap.begin();

      ::user::view_creator_data * pcreatordata;

      id id;

      while(pos != m_viewmap.end())
      {

         if(pcreatordata->m_pdoc != NULL && pcreatordata->m_pdoc != pdocument && (pSender == NULL || pSender->get_document() != pcreatordata->m_pdoc))
         {

            pcreatordata->m_pdoc->update_all_views(pSender, lHint, pHint);

         }

         pos++;

      }

   }


} // namespace user



