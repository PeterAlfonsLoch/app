
//#include "framework.h"
//#include "base/user/user.h"




namespace simple_ui
{


   top::top(::aura::application * papp) :
      ::object(papp),
      ::simple_ui::style(papp)
   {

      m_bDrag = false;

   }


   top::~top()
   {

   }


   void top::install_message_handling(::message::dispatch * pdispatch)
   {

      ::simple_ui::interaction::install_message_handling(pdispatch);

      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN,pdispatch,this,&top::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP,pdispatch,this,&top::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE,pdispatch,this,&top::_001OnMouseMove);

   }


   void top::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create,pcreate,pobj);

      if(pcreate->previous())
         return;

   }


   void top::_001OnLButtonDown(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if (pobj->previous())
         return;

      get_wnd()->show_keyboard(false);

      m_bLButtonDown = true;
      m_bDrag = false;

      m_ptLButtonDown = pmouse->m_pt;
      m_ptLButtonDownPos = m_ptLButtonDown;
      ScreenToClient(&m_ptLButtonDownPos);
      SetCapture();

      pmouse->m_bRet = true;

   }


   void top::_001OnLButtonUp(signal_details * pobj)
   {

      m_bLButtonDown = false;

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if(pmouse->previous())
         return;

      ReleaseCapture();

      m_bDrag = false;

      pobj->m_bRet = true;

   }


   void top::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      if (m_bLButtonDown)
      {
         if (!m_bDrag)
         {
            m_bDrag = true;
            POINT ptNow = pmouse->m_pt;
            point pt;
            pt.x = ptNow.x - m_ptLButtonDownPos.x;
            pt.y = ptNow.y - m_ptLButtonDownPos.y;
            MoveWindow(pt);
            m_bDrag = false;
         }
         pobj->m_bRet = true;

      }
      else
      {
         if(pobj->previous())
            return;

         pobj->m_bRet = true;
      }

   }


} // namespace fontopus


