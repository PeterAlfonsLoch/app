#include "axis/user/user.h"


namespace database
{


   namespace user
   {


      interaction::interaction()
      {

      }


      interaction::~interaction()
      {

      }


      void interaction::install_message_handling(::message::dispatch * pinterface)
      {

         ::simple_ui::interaction::install_message_handling(pinterface);

         IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &interaction::_001OnCreate);
         IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &interaction::_001OnSize);
         IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &interaction::_001OnMove);
         IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &interaction::_001OnShowWindow);

      }


      void interaction::_001OnCreate(signal_details * pobj)
      {
         
         UNREFERENCED_PARAMETER(pobj);

         if(pobj->previous())
            return;

         set_data_server(&Application.dataserver());

         if(m_dataidWindow.is_null())
         {

            m_dataidWindow = typeid(*this).name();

         }

         update_data_id();

      }


      void interaction::_001OnMove(signal_details * pobj)
      {

         UNREFERENCED_PARAMETER(pobj);

      }


      void interaction::_001OnSize(signal_details * pobj)
      {

         pobj->previous();
         UNREFERENCED_PARAMETER(pobj);

      }


      void interaction::_001OnShowWindow(signal_details * pobj)
      {

         UNREFERENCED_PARAMETER(pobj);

      }


      void interaction::WindowDataEnableSaveWindowRect(bool bEnable)
      {
         m_bEnableSaveWindowRect = bEnable;
      }

      bool interaction::WindowDataSaveWindowRect()
      {

         single_lock sl(m_spmutex, true);

         bool bSave = false;

         if(m_bEnableSaveWindowRect)
         {

            defer_update_display();

            ::database::id idWindow    = m_dataidWindow;

            ::id idKey                 = ".local://WindowRect." + m_strDisplay;

            sl.unlock();

            bSave = SaveWindowRect_(
               idWindow,
               idKey,
               this);
         }

         return true;

      }


      bool interaction::WindowDataLoadWindowRect(bool bForceRestore, bool bInitialFramePosition)
      {

         single_lock sl(m_spmutex, true);

         bool bLoad = false;

         keep < bool > keepEnable(&m_bEnableSaveWindowRect, false, m_bEnableSaveWindowRect, true);

         defer_update_display();

         ::database::id idWindow       = m_dataidWindow;

         ::id idKey                    = ".local://WindowRect." + m_strDisplay;

         sl.unlock();

         bLoad = LoadWindowRect_(idWindow, idKey, this, bForceRestore, bInitialFramePosition);

         if(!bLoad && (bForceRestore || bInitialFramePosition))
         {

            bool bRestore = good_restore(NULL,null_rect(),true) >= 0;

            return bRestore;

         }

         return bLoad;

      }


      bool interaction::IsFullScreen()
      {

         return false;

      }


      bool interaction::LoadWindowRect_(::database::id key, ::database::id idIndex, sp(::user::interaction) pwindow, bool bForceRestore, bool bInitialFramePosition)
      {

         try
         {
            
            sync_io_error error;

            ::file::byte_stream_memory_buffer memstream(get_app());

            if(!data_get(key,idIndex,memstream))
               return false;

            memstream.seek_to_begin();

            int iBefore = 0;

            memstream >> iBefore;

            set_appearance_before((::user::EAppearance)iBefore);

            bool bZoomed = false;

            memstream >> bZoomed;

            bool bFullScreen = false;

            memstream >> bFullScreen;

            bool bIconic = false;

            memstream >> bIconic;

            int iAppearance = 0;

            memstream >> iAppearance;

            ::user::EAppearance eappearance = (::user::EAppearance) iAppearance;

            rect rectWindow;

            memstream >> rectWindow;

            if(error)
               return false;

            if(!bForceRestore)
            {

               if(bZoomed || (bInitialFramePosition && m_eappearanceBefore == ::user::AppearanceZoomed))
               {

                  pwindow->set_appearance(::user::AppearanceZoomed);

                  pwindow->best_wkspace(NULL,rectWindow,true);

               }
               else if(bFullScreen || (bInitialFramePosition && m_eappearanceBefore == ::user::AppearanceFullScreen))
               {

                  pwindow->set_appearance(::user::AppearanceFullScreen);

                  pwindow->best_monitor(NULL,rectWindow,true);

               }
               else if(bIconic && !bInitialFramePosition)
               {

                  pwindow->set_appearance(::user::AppearanceIconic);

                  pwindow->good_iconify(NULL,rectWindow,true);

               }
               else if(::user::is_docking_appearance(eappearance))
               {

                  pwindow->make_zoneing(NULL,rectWindow,true,&eappearance);

               }
               else
               {

                  pwindow->set_appearance(::user::AppearanceNormal);

                  pwindow->good_restore(NULL,rectWindow,true);

               }

            }
            else
            {

               pwindow->set_appearance(::user::AppearanceNormal);

               pwindow->good_restore(NULL,rectWindow,true);

            }

            return true;

         }
         catch(exit_exception & e)
         {
            throw e;
         }
         catch (...)
         {

            return false;

         }


      }


      bool interaction::SaveWindowRect_(::database::id key, ::database::id idIndex,  sp(::user::interaction) pwindow)
      {
         //WINDOWPLACEMENT wp;
         //pwindow->GetWindowPlacement(&wp);
         ::file::byte_stream_memory_buffer memstream(get_app());
         ::file::byte_stream_memory_buffer memstreamGet(get_app());
         bool bGet = data_get(
            key,
            idIndex,
            memstreamGet);
         memstreamGet.seek_to_begin();
         int iBeforeOld = 0;
         bool bZoomedOld = false;
         bool bFullScreenOld = false;
         bool bIconicOld = false;
         int iAppearanceOld = 0;
         rect rectOld;
         if(bGet)
         {
            try
            {
               sync_io_error error;
               memstreamGet >> iBeforeOld;
               memstreamGet >> bZoomedOld;
               memstreamGet >> bFullScreenOld;
               memstreamGet >> bIconicOld;
               memstreamGet >> iAppearanceOld;
               memstreamGet >> rectOld;
               bGet = error.none();
            }
            catch (...)
            {
               bGet = false;
            }
         }
         int iBefore = (int) get_appearance_before();
         memstream << iBefore;
         bool bZoomed = pwindow->WfiIsZoomed() != FALSE;
         memstream << bZoomed;
         bool bFullScreen = pwindow->WfiIsFullScreen();
         memstream << bFullScreen;
         bool bIconic = pwindow->WfiIsIconic();
         memstream << bIconic;
         int iAppearance = (int) pwindow->get_appearance();
         memstream << iAppearance;
         if(bGet && (bZoomed || bFullScreen || bIconic || ::user::is_docking_appearance((::user::EAppearance)iAppearance)))
         {
            memstream << rectOld;
         }
         else
         {
            rect rect;
            pwindow->GetWindowRect(rect);
            memstream << rect;
         }
         return data_set(key, idIndex, memstream);
      }


      void interaction::_001WindowRestore()
      {

         set_appearance(::user::AppearanceNormal);

         WindowDataLoadWindowRect(true);

      }


      string interaction::calc_display()
      {

         string strDisplay;

         rect rectNormal;

         get_rect_normal(rectNormal);

         rect rectScreen;

         best_monitor(rectScreen, rectNormal);

         strDisplay.Format("Display(%d, %d)", rectScreen.width(), rectScreen.height());

         return strDisplay;

      }

      bool interaction::does_display_match()
      {

         single_lock sl(m_spmutex, true);

         if(m_strDisplay.is_empty())
            return false;

         return m_strDisplay == calc_display();

      }

      void interaction::defer_update_display()
      {

         if(m_strDisplay.is_empty())
         {

            if(!data_get(m_dataidWindow,"local://lastdisplay",m_strDisplay) || m_strDisplay.is_empty())
            {

               m_strDisplay = calc_display();

            }

         }
         else
         {

            m_strDisplay = calc_display();

            data_set(m_dataidWindow,"local://lastdisplay",m_strDisplay);

         }

      }



      bool interaction::on_simple_command(e_simple_command ecommand, lparam lparam, LRESULT & lresult)
      {

         if(::user::interaction::on_simple_command(ecommand, lparam, lresult))
            return true;

         switch(ecommand)
         {
         case simple_command_load_window_rect:
            WindowDataLoadWindowRect(lparam != FALSE);
            break;
         default:
            break;
         }


         return false;

      }

      id interaction::calc_data_id()
      {

         string str;

         sp(::database::user::interaction) puiParent = GetParent();

         if (puiParent.is_set())
         {

            str = puiParent->calc_data_id().m_id;

         }

         if (str.has_char())
         {

            str += ".";

         }

         return str + m_dataidWindow.m_id;

      }

      bool interaction::on_before_set_parent(sp(::user::interaction) puiParent)
      {

         if (!::user::interaction::on_before_set_parent(puiParent))
            return false;
         
         WindowDataEnableSaveWindowRect(false);

         return true;

      }


      void interaction::on_set_parent(sp(::user::interaction) puiParent)
      {

         try
         {

            ::user::interaction::on_set_parent(puiParent);

         }
         catch (...)
         {

         }

         update_data_id();

      }


   } // namespace user


} //namespace database

















