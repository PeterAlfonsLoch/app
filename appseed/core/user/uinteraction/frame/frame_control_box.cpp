#include "framework.h"


namespace uinteraction
{


   namespace frame
   {


      control_box::control_box(sp(base_application) papp) :
         element(papp),
         ::user::interaction(papp)
      {

            m_bDrag = false;

         }


      control_box::~control_box()
      {

      }

      void control_box::_001OnLButtonDown(signal_details * pobj)
      {

         SCAST_PTR(::message::mouse, pmouse, pobj);


         m_bDrag = true;

         m_ptDrag = pmouse->m_pt;

         ScreenToClient(&m_ptDrag);

         set_capture();

         pmouse->m_bRet = true;

      }


      void control_box::_001OnLButtonUp(signal_details * pobj)
      {

         SCAST_PTR(::message::mouse, pmouse, pobj);

         drag(pmouse->m_pt);

         m_bDrag = false;

         release_capture();


         pmouse->m_bRet = true;
      }


      void control_box::_001OnMouseMove(signal_details * pobj)
      {

         SCAST_PTR(::message::mouse, pmouse, pobj);

         if (m_bDrag)
         {
            drag(pmouse->m_pt);
         }

         pmouse->m_bRet = true;

      }

      void control_box::drag(point pt)
      {

         int x = pt.x - m_ptDrag.x;

         if (x < 0)
            x = 0;

         rect rectParent;

         get_parent()->GetWindowRect(rectParent);

         rect rectClient;

         GetClientRect(rectClient);

         if (x > rectParent.right - rectClient.width())
            x = rectParent.right - rectClient.width();

         if (x < rectParent.left)
            x = rectParent.left;

         rect rectWindow;

         GetWindowRect(rectWindow);

         point ptClient(x, rectWindow.top);

         get_parent()->ScreenToClient(ptClient);

         SetWindowPos(ZORDER_TOP, ptClient.x, ptClient.y, 0, 0, SWP_NOSIZE);


      }

      void control_box::_001OnShowWindow(signal_details * pobj)
      {

         SCAST_PTR(::message::show_window, pshow, pobj)

            m_bDrag = false;

         m_bShowAttempt = false;

         if (pshow->m_bShow)
         {

            m_dwShowTime = ::get_tick_count();

         }

      }


      void control_box::_001OnTimer(signal_details * pobj)
      {

//         SCAST_PTR(::message::timer, ptimer, pobj)

         if (IsWindowVisible())
         {
            if (m_bDrag)
            {
               m_dwShowTime = ::get_tick_count();
            }
            else
            {
               if (m_pworkset->GetDrawWindow().cast < simple_frame_window >() != NULL)
               {

                  if (m_pworkset->GetDrawWindow().cast < simple_frame_window >()->WfiIsFullScreen())
                  {

                     rect rectWindow;

                     GetWindowRect(rectWindow);

                     if (rectWindow.contains(Session.m_ptCursor))
                     {
                        m_dwShowTime = ::get_tick_count();
                     }
                     else
                     {
                        if ((::get_tick_count() - m_dwShowTime) > (884))
                        {


                           ShowWindow(SW_HIDE);

                        }

                     }

                  }


               }

            }
         }
         else if (m_bShowAttempt)
         {
            if ((::get_tick_count() - m_dwShowTime) > 284)
            {
               if (m_pworkset->GetDrawWindow().cast < simple_frame_window >() != NULL)
               {

                  if (m_pworkset->GetDrawWindow().cast < simple_frame_window >()->WfiIsFullScreen())
                  {

                     rect rectWindow;

                     GetWindowRect(rectWindow);

                     if (Session.m_ptCursor.x >= rectWindow.left && Session.m_ptCursor.y <= rectWindow.right && Session.m_ptCursor.y == 0)
                     {

                        ShowWindow(SW_SHOW);

                     }

                     m_bShowAttempt = false;

                  }

               }

            }
         }
         else
         {

            if (m_pworkset->GetDrawWindow().cast < simple_frame_window >()->WfiIsFullScreen())
            {

               rect rectWindow;

               GetWindowRect(rectWindow);

               point pt(0, 0);

               try
               {

                  pt = Session.m_ptCursor;

               }
               catch (...)
               {
               }




               if (pt.x >= rectWindow.left && pt.x <= rectWindow.right && pt.y == 0)
               {

                  m_bShowAttempt = true;
                  m_dwShowTime = ::get_tick_count();

               }

            }

         }

      }


      void control_box::_001OnCreate(signal_details * pobj)
      {

         UNREFERENCED_PARAMETER(pobj);
//         SCAST_PTR(::message::create, pcreate, pobj)

            SetTimer(123, 184, NULL);

      }


      void control_box::install_message_handling(::message::dispatch *pinterface)
      {

         ::user::interaction::install_message_handling(pinterface);

         IGUI_WIN_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &control_box::_001OnShowWindow);
         IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &control_box::_001OnTimer);
         IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &control_box::_001OnCreate);
         IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &control_box::_001OnMouseMove);
         IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &control_box::_001OnLButtonDown);
         IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &control_box::_001OnLButtonUp);

      }



   } // namespace frame


} // namespace uinteraction




