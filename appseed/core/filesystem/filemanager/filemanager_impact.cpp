//#include "framework.h"


namespace filemanager
{


   impact::impact()
   {

      m_pmanager = NULL;

      m_bEditConnectInit = false;

   }

   impact::~impact()
   {

   }


   void impact::install_filemanager_impact_handling(command_target * ptarget,::message::dispatch * pdispatch)
   {

      try
      {

         if(ptarget != NULL)
         {

            ptarget->connect_update_cmd_ui("edit_paste",this, &impact::_001OnUpdateEditPaste);

            ptarget->connect_command("edit_paste",this, &impact::_001OnEditPaste);

         }

         if(pdispatch != NULL)
         {

            IGUI_WIN_MSG_LINK(WM_APP + 1024,pdispatch,this,&impact::_001OnOperationDocMessage);

         }

      }
      catch(...)
      {

      }

   }

   
   void impact::install_filemanager_impact_handling()
   {

      if(m_bEditConnectInit)
         return;

      m_bEditConnectInit = true;

      try
      {

         //::command_target * ptarget = dynamic_cast <::command_target *> (this);

         ::user::interaction * pinteraction = dynamic_cast <::user::interaction *>(this);

         if(pinteraction != NULL)
         {

            //::message::dispatch * pdispatch = dynamic_cast <::message::dispatch *> (this);

            install_filemanager_impact_handling(pinteraction,pinteraction->m_pimpl);

         }

      }
      catch(...)
      {

      }


      try
      {

         ::data::data * pdata = dynamic_cast <::data::data *> (this);

         if(pdata != NULL)
         {

            for(index i = 0; i < pdata->get_data_bound_view_count(); i++)
            {

               try
               {

                  ::aura::impact * pview = pdata->get_data_bound_view(i);

                  if(pview != NULL)
                  {

                     install_filemanager_impact_handling(pview,pview->m_pimpl);

                  }

               }
               catch(...)
               {

               }

            }

         }

      }
      catch(...)
      {

      }

   }


   ::aura::impact * impact::get_this_view()
   {

      return dynamic_cast <::aura::impact *> (this);

   }


   ::fs::item & impact::get_filemanager_item()
   {

      return get_filemanager_manager()->get_filemanager_item();

   }


   sp(manager) impact::get_filemanager_manager()
   {

      return m_pmanager;

   }


   sp(data) impact::get_filemanager_data()
   {

      return  get_filemanager_manager()->get_filemanager_data();

   }


   sp(manager_template) impact::get_filemanager_template()
   {

      return  get_filemanager_data()->get_filemanager_template();

   }


   void impact::on_update(::aura::impact * psender, LPARAM lhint, object * phint)
   {

      UNREFERENCED_PARAMETER(psender);
      UNREFERENCED_PARAMETER(lhint);

      if (phint != NULL)
      {
         if (base_class < update_hint > ::bases(phint))
         {
            update_hint * puh = (update_hint *)phint;
            if (puh->is_type_of(update_hint::TypeInitialize))
            {
               if (m_pmanager == NULL
                  && (puh->m_pview == NULL ||
                  puh->m_pview == (this)))
               {

                  m_pmanager = puh->m_pmanager;

                  install_filemanager_impact_handling();

               }

            }
            else if(puh->is_type_of(update_hint::TypeSynchronizePath))
            {
               if(puh->m_strPath == get_filemanager_item().m_strPath)
               {
                  browse_sync(puh->m_actioncontext + ::action::source_sync);
               }
               else
               {
                  knowledge(puh->m_strPath, puh->m_actioncontext + ::action::source_sync);
               }
            }

         }
      else if(base_class < ::user::view_update_hint > ::bases(phint))
      {
         sp(::user::view_update_hint) puh = phint;
         if(puh->is_type_of(::user::view_update_hint::hint_create_views))
         {
            if(m_pmanager == NULL
               && (puh->oprop("data").cast < impact >() == NULL ||
               puh->oprop("data").cast < impact >() == (this)))
            {
               m_pmanager = puh->oprop("manager").cast <manager>();
            }
         }
      }
      }
   }

   
   void impact::_001Refresh()
   {

      get_filemanager_manager()->FileManagerBrowse(&get_filemanager_item(),::action::source_sync);

   }


   void impact::browse_sync(::action::context actioncontext)
   {
      
      UNREFERENCED_PARAMETER(actioncontext);

   }

   void impact::knowledge(const string & strPath, ::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(strPath);
      UNREFERENCED_PARAMETER(actioncontext);

   }

   void impact::_001OnUpdateEditPaste(signal_details * pobj)
   {
      SCAST_PTR(::aura::cmd_ui,pcmdui,pobj)
         pcmdui->m_pcmdui->Enable(Session.copydesk().get_file_count() > 0);
      pobj->m_bRet = true;
   }


   void impact::_001OnEditPaste(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      stringa stra;

      Session.copydesk().get_filea(stra);
      string strDir;
      strDir = get_filemanager_item().m_strPath;

      ::aura::impact * pview  = get_this_view();

      if(pview == NULL)
         return;

      tab_view * ptabview = get_this_view()->GetTypedParent < tab_view >();

      if(ptabview != NULL)
      {

         ptabview->filemanager_manager().get_operation_doc(true)->m_thread.queue_copy(stra,strDir,NULL,true,false,this,WM_APP + 1024,4096);

         ptabview->filemanager_manager().get_operation_doc(true)->m_thread.kick();

      }
      pobj->m_bRet =true;

      /* for(int32_t i = 0; i < stra.get_size(); i++)
      {
      ::CopyFileW(
      L"\\\\?\\" + ::str::international::utf8_to_unicode(stra[i]),
      L"\\\\?\\" + ::str::international::utf8_to_unicode(strDir + System.file().title(stra[i]))), TRUE);
      }*/
      //get_document()->update_all_views(NULL, 123);
   }


   void impact::_001OnOperationDocMessage(signal_details * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      if(pbase->m_wparam == 4096)
      {

         if(pbase->m_lparam == 0)
         {

            _001Refresh();

         }

      }

   }




} // namespace filemanager




