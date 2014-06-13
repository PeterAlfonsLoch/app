#include "framework.h"


namespace database
{


   namespace user
   {


      interaction::interaction()
      {

         m_bEnableSaveWindowRect = false;

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
         //         SCAST_PTR(::message::show_window, pshowwindow, pobj)
         if(get_parent() == NULL)
         {
         }
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

            m_strDisplay = calc_display();

            ::database::id idWindow    = m_dataidWindow;

            ::id idKey                 = "WindowRect." + m_strDisplay;

            sl.unlock();

            bSave = SaveWindowRect_(
               idWindow,
               idKey,
               this);
         }

         return true;

      }


      bool interaction::WindowDataLoadWindowRect(bool bForceRestore)
      {

         single_lock sl(m_spmutex, true);

         bool bLoad = false;

         keeper < bool > keepEnable(&m_bEnableSaveWindowRect, false, m_bEnableSaveWindowRect, true);

         m_strDisplay = calc_display();

         ::database::id idWindow       = m_dataidWindow;

         ::id idKey                    = "WindowRect." + m_strDisplay;

         sl.unlock();

         bLoad = LoadWindowRect_(idWindow, idKey, this, bForceRestore);

         return bLoad;

      }


      bool interaction::IsFullScreen()
      {

         return false;

      }


      bool interaction::LoadWindowRect_(::database::id key, ::database::id idIndex, sp(::user::interaction) pwindow, bool bForceRestore)
      {

         try
         {

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


            rect rectWindow;

            memstream >> rectWindow;

            rect rectRestore;

            if(Session.get_good_restore(rectRestore,rectWindow))
            {

               SetWindowPos(
                  ZORDER_TOP,
                  rectRestore.left,
                  rectRestore.top,
                  rectRestore.width(),
                  rectRestore.height(),
                  bForceRestore && (!bZoomed && !bFullScreen && !bIconic) ? SWP_SHOWWINDOW : 0);

            }

            if(!bForceRestore)
            {

               if(bZoomed)
               {

                  pwindow->WfiMaximize();

               }
               else if(bFullScreen)
               {

                  pwindow->WfiFullScreen();

               }
               else if(bIconic)
               {

                  pwindow->WfiMinimize();

               }

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
         rect rectOld;
         if(bGet)
         {
            try
            {
               memstreamGet >> iBeforeOld;
               memstreamGet >> bZoomedOld;
               memstreamGet >> bFullScreenOld;
               memstreamGet >> bIconicOld;
               memstreamGet >> rectOld;
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
         if(bGet && (bZoomed || bFullScreen || bIconic))
         {
            memstream << &rectOld;
         }
         else
         {
            rect rect;
            pwindow->GetWindowRect(rect);
            memstream << &rect;
         }
         return data_set(key, idIndex, memstream);
      }


      void interaction::_001WindowRestore()
      {

         if (m_pimpl != NULL)
         {

            keeper < bool > keepEnable(&m_bEnableSaveWindowRect, false, m_bEnableSaveWindowRect, true);

            m_pimpl->m_eappearance = ::user::AppearanceNormal;

            m_pimpl->_001WindowRestore();

         }
            
         WindowDataLoadWindowRect(true);
         
         m_eappearance = ::user::AppearanceNormal;

      }


      string interaction::calc_display()
      {

         string strDisplay;

         rect rectScreen;

         Session.get_best_monitor(rectScreen);

         strDisplay.Format("Display(%d, %d)", rectScreen.width(), rectScreen.height());

         return strDisplay;

      }

      bool interaction::does_display_match()
      {

         single_lock sl(m_spmutex, true);

         return m_strDisplay == calc_display();

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

         sp(::database::user::interaction) puiParent = get_parent();

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

















