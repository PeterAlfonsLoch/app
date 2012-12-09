#include "framework.h"


namespace userbase
{


   split_bar::split_bar(::ca::application * papp) :
      ca(papp)
   {
      
      m_pparent                                 = NULL;
      m_dMinimumRate                            = 0.1;
      m_dMaximumRate                            = 0.9;
      m_dRate                                   = -1.0;
      m_dwPosition                              = 1;
      m_dwMaxPosition                           = (DWORD) -1;

   }

   split_bar::~split_bar()
   {


   }



   bool split_bar::create(split_layout * pparent)
   {
      m_pparent = pparent;
//      int nClassStyle = 0;
//      const char * lpClassName = System.RegisterWndClass(
         //nClassStyle,
         //0,
         //0,
         //0);
   //   rect rect(0, 0, 0, 0);
      if(!::user::interaction::create(pparent, 0))
      {
         System.simple_message_box(NULL, "Could not create Split Bar");
         return FALSE;
      }

      return TRUE;
   }


   void split_bar::layout()
   {

   }


   void split_bar::_001OnDraw(::ca::graphics *pdc)
   {
      UNREFERENCED_PARAMETER(pdc);
   }


   bool split_bar::pre_create_window(CREATESTRUCT& cs)
   {
      cs.style &= ~WS_BORDER;

      return ::user::interaction::pre_create_window(cs);
   }


   void split_bar::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      //IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &split_bar::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &split_bar::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &split_bar::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &split_bar::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &split_bar::_001OnMouseMove);
   }

   void split_bar::_001OnLButtonDown(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj);
      single_lock sl(&m_pparent->m_mutex, TRUE);
      m_pparent->m_iIndex = m_iIndex;
      if(m_iIndex >= 0 && m_iIndex < m_pparent->m_splitbara.get_count()
         && !m_pparent->m_panea[m_iIndex].m_bFixedSize)
      {
         m_pparent->m_iState = split_layout::stateDragging;
         set_capture();
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
   }

   void split_bar::_001OnLButtonUp(gen::signal_object * pobj)
   {
      SCAST_PTR(::gen::message::mouse, pmouse, pobj);
      single_lock sl(&m_pparent->m_mutex, TRUE);
      if(m_pparent->m_iIndex == m_iIndex)
      {
         m_pparent->m_iState = split_layout::stateInitial;
         System.release_capture_uie();
         pmouse->m_bRet = true;
         pmouse->set_lresult(1);
      }
   }

   void split_bar::_001OnMouseMove(gen::signal_object * pobj)
   {
      
      SCAST_PTR(::gen::message::mouse, pmouse, pobj);
      
      single_lock sl(&m_pparent->m_mutex, TRUE);
      
      point ptClient = pmouse->m_pt;

      m_pparent->ScreenToClient(&ptClient);

      if(m_iIndex >= 0 && m_iIndex < m_pparent->m_splitbara.get_count() && !m_pparent->m_panea[m_iIndex].m_bFixedSize)
      {

         if(m_pparent->GetSplitOrientation() == split_layout::orientation_horizontal)
         {

            pmouse->m_ecursor = ::visual::cursor_size_vertical;

         }
         else
         {

            pmouse->m_ecursor = ::visual::cursor_size_horizontal;

         }

      }

      if((m_pparent->m_iState == split_layout::stateDragging) && (m_iIndex == m_pparent->m_iIndex))
      {
         int nPos;
         bool bMove;
         nPos = m_pparent->GetPos(ptClient.x, ptClient.y);
         if(m_iIndex <= 0)
         {
            bMove = nPos > m_pparent->GetMinPos();
         }
         else
         {
            bMove = nPos > (int) m_pparent->m_splitbara[m_iIndex - 1].m_dwPosition;
         }
         if(m_pparent->get_pane_count() >= m_iIndex )
         {
            bMove = bMove && nPos < m_pparent->GetMaxPos();
         }
         else
         {
            bMove = bMove && nPos < (int) m_pparent->m_splitbara[m_iIndex].m_dwPosition;
         }
         if(bMove)
         {
            bMove = m_pparent->get_normal_dimension() > 0;
         }
         double dRate = -1.0;
         if(bMove)
         {
            dRate = (double) nPos / (double) m_pparent->get_normal_dimension();
            if(dRate < m_dMinimumRate)
            {
               dRate = m_dMinimumRate;
               nPos = (int) (m_pparent->get_normal_dimension() * dRate);
            }
            else if(dRate > m_dMaximumRate)
            {
               dRate = m_dMaximumRate;
               nPos = (int) (m_pparent->get_normal_dimension() * dRate);
            }
         }
         if(bMove)
         {
            bMove = nPos != (int) m_pparent->m_splitbara[m_iIndex].m_dwPosition;
         }

         TRACE("split_layout::RelayChildEvent nPos %d\nOldPos", m_pparent->m_splitbara[m_iIndex].m_dwPosition);
         TRACE("split_layout::RelayChildEvent nPos %d\n", nPos);
         if(bMove)
         {

            m_pparent->m_splitbara[m_iIndex].m_dwPosition = nPos;
            m_pparent->m_splitbara[m_iIndex].m_dRate = dRate;
            m_pparent->layout();
         }
      }
      pmouse->m_bRet = true;
      pmouse->set_lresult(1);
   }

} // namespace userbase
