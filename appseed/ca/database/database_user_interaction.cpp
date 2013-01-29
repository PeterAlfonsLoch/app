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

      void interaction::install_message_handling(::gen::message::dispatch * pinterface)
      {
         ::user::interaction::install_message_handling(pinterface);
         IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &interaction::_001OnCreate);
         IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &interaction::_001OnSize);
         IGUI_WIN_MSG_LINK(WM_MOVE, pinterface, this, &interaction::_001OnMove);
         IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &interaction::_001OnShowWindow);
      }

      void interaction::_001OnCreate(gen::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);

         if(pobj->previous())
            return;

         set_server(Application.get_data_server());
         if(m_dataidWindow.is_null())
         {
            string strKey;
            strKey = System.m_strAppName;
            strKey += ".";
            strKey += typeid(*this).name();
            m_dataidWindow = strKey;
         }
         if(m_dataid.is_null())
         {
            m_dataid = m_dataidWindow;
         }
      }



      void interaction::_001OnMove(gen::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }

      void interaction::_001OnSize(gen::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
      }

      void interaction::_001OnShowWindow(gen::signal_object * pobj)
      {
         UNREFERENCED_PARAMETER(pobj);
//         SCAST_PTR(::gen::message::show_window, pshowwindow, pobj)
         if(get_parent() == NULL)
         {
#if !core_level_1 && !core_level_2 && defined(WINDOWS)
            if(GetExStyle() && WS_EX_LAYERED)
            {
               if(IsZoomed())
               {
               }
               else if(IsFullScreen())
               {
               }
               else if(IsIconic())
               {
               }
               else
               {

               }
            }
#endif
         }
      }


      void interaction::WindowDataEnableSaveWindowRect(bool bEnable)
      {
         m_bEnableSaveWindowRect = bEnable;
      }

      bool interaction::WindowDataSaveWindowRect()
      {
         bool bSave = false;
         if(m_bEnableSaveWindowRect)
         {
            bSave = SaveWindowRect_(
               m_dataidWindow,
               "WindowRect",
               this);
         }
         return true;
      }

      bool interaction::WindowDataLoadWindowRect(bool bForceRestore)
      {
         bool bLoad = false;
         keeper < bool > keepEnable(&m_bEnableSaveWindowRect, false, m_bEnableSaveWindowRect, true);
         bLoad = LoadWindowRect_(
                     m_dataidWindow,
                     "WindowRect",
                     this,
                     bForceRestore);
         return bLoad;
      }


      bool interaction::IsFullScreen()
      {
         return false;
      }

      bool interaction::LoadWindowRect_(
         ::database::id key, ::database::id idIndex,
         ::user::interaction * pWnd,
         bool bForceRestore)
      {
         gen::byte_stream_memory_file memstream(get_app());
         if(!data_get(key, idIndex, memstream))
            return false;
         memstream.seek_to_begin();
         bool bZoomed = false;
         memstream >> bZoomed;
         if(!bForceRestore && bZoomed)
         {
            pWnd->ShowWindow(SW_MAXIMIZE);
         }
         bool bFullScreen = false;
         memstream >> bFullScreen;
         if(!bForceRestore && bFullScreen)
         {
            pWnd->ShowWindowFullScreen();
         }
         bool bIconic = false;
         memstream >> bIconic;
         if(!bForceRestore && bIconic)
         {
            pWnd->ShowWindow(SW_MINIMIZE);
         }
         if(bForceRestore)
         {
            pWnd->ShowWindow(SW_RESTORE);
         }
         if(bForceRestore || (!bZoomed && !bFullScreen && !bIconic))
         {
            rect rect;
            memstream >> rect;
            pWnd->SetWindowPos(0, rect.left,
               rect.top, rect.width(), rect.height(), SWP_NOZORDER | SWP_NOACTIVATE);
         }
         return true;
      }
      bool interaction::SaveWindowRect_(
         ::database::id key, ::database::id idIndex,  ::user::interaction * pWnd)
      {
         //WINDOWPLACEMENT wp;
         //pWnd->GetWindowPlacement(&wp);
         gen::byte_stream_memory_file memstream(get_app());
         gen::byte_stream_memory_file memstreamGet(get_app());
         bool bGet = data_get(
            key,
            idIndex,
            memstreamGet);
         memstreamGet.seek_to_begin();
         bool bZoomedOld = false;
         bool bFullScreenOld = false;
         bool bIconicOld = false;
         rect rectOld;
         if(bGet)
         {
            memstreamGet >> bZoomedOld;
            memstreamGet >> bFullScreenOld;
            memstreamGet >> bIconicOld;
            memstreamGet >> rectOld;
         }
         bool bZoomed = pWnd->IsZoomed() != FALSE;
         memstream << bZoomed;
         bool bFullScreen = pWnd->IsFullScreen();
         memstream << bFullScreen;
         bool bIconic = pWnd->IsIconic();
         memstream << bIconic;
         if(bGet && (bZoomed || bFullScreen || bIconic))
         {
            memstream << &rectOld;
         }
         else
         {
            rect rect(pWnd->m_rectParentClient);
            memstream << &rect;
         }
         return data_set(key, idIndex, memstream);
      }

      void interaction::_001WindowRestore()
      {
         WindowDataLoadWindowRect(true);
      }

   } // namespace user

} //namespace database
