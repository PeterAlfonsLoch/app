#include "framework.h"


namespace estamira
{

   character::character(::aura::application * papp, index iIndex) :
      object(papp),
      m_ts(papp)
   {

      m_iIndex = iIndex;

      m_dwUpTime = 1000;
      
      m_ekeyLeft = ::user::key_left;
      m_ekeyUp = ::user::key_up;
      m_ekeyRight = ::user::key_right;

   }

   character::~character()
   {

   }

   void character::install_message_handling(::message::dispatch * pdispatch)
   {
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pdispatch, this, &character::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pdispatch, this, &character::_001OnKeyUp);
      //IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &character::_001OnLButtonDown);
      //IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pdispatch, this, &character::_001OnLButtonUp);
      //IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &character::_001OnMouseMove);

   }


   bool character::init(string strTileMap, game * pgame)
   {

      m_pgame = pgame;

      install_message_handling(pgame->m_pui->m_pimpl);

      m_pt.x = 0;
      m_pt.y = 0;
      m_ptStart.x = System.math().RandRange(0, 16384);
      m_ptStart.y = 120;

      if (!m_ts.load_tilemap(strTileMap))
      {

         return false;

      }

      m_dwLastChangeXDir = get_tick_count();

      m_strTileMap = strTileMap;

      return true;

   }

   void character::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      stringa stra;

      if (m_iMoveX > 0)
      {
         stra.add("right");
         stra.add("right1");
         stra.add("right2");
      }
      else if (m_iMoveX < 0)
      {
         stra.add("left");
         stra.add("left1");
         stra.add("left2");
      }
      else
      {
         stra.add("down");
      }

      int iDelay = 84;

      int iUp = 0;
      int iUpMax = 48;
      if (get_tick_count() - m_dwLastUp < m_dwUpTime)
      {
         iUp = iUpMax * sin(3.1415 * double(get_tick_count() - m_dwLastUp) / double(m_dwUpTime));
      }
      m_ptNow.y = m_ptStart.y + m_pt.y - iUp;
      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      m_ts.draw(pgraphics, stra[((get_tick_count() - m_dwLastChangeXDir) / iDelay) % stra.get_size()], m_ptNow.x, m_ptNow.y);

   }


   void character::_001OnKeyDown(signal_details * pobj)
   {
      
      SCAST_PTR(::message::key, pkey, pobj);

      if (pkey->m_ekey == m_ekeyUp)
      {

         if (get_tick_count() - m_dwLastUp > m_dwUpTime)
         {

            m_dwLastUp = get_tick_count();

         }

      }
      else if (pkey->m_ekey == m_ekeyLeft)
      {

         if (m_pgame->m_bKeyPulse)
         {

            moveLeft();

         }
         else
         {

            m_bLeft = true;

            m_bRight = false;

         }

      }
      else if (pkey->m_ekey == m_ekeyRight)
      {

         if (m_pgame->m_bKeyPulse)
         {

            moveRight();

         }
         else
         {

            m_bLeft = false;

            m_bRight = true;

         }

      }

   }

   void character::_001OnKeyUp(signal_details * pobj)
   {
      
      SCAST_PTR(::message::key, pkey, pobj);
    
      if (pkey->m_ekey == m_ekeyLeft)
      {

         if (m_pgame->m_bKeyPulse)
         {

            moveX(0);

         }
         else
         {

            m_bLeft = false;

            m_bRight = false;

         }
            
      }
      else if (pkey->m_ekey == m_ekeyRight)
      {

         if (m_pgame->m_bKeyPulse)
         {

            moveX(0);

         }
         else
         {

            m_bLeft = false;

            m_bRight = false;

         }

      }

   }

   void character::moveX(int iMoveX)
   {

      if (iMoveX < 0 && canMoveLeft())
      {

         iMoveX = -1;

      }
      else if (iMoveX > 0 && canMoveRight())
      {

         iMoveX = 1;

      }
      else
      {

         iMoveX = 0;

      }

      if (m_iMoveX != iMoveX)
      {

         m_dwLastChangeXDir = ::get_tick_count();

         m_ptStart.x = m_ptNow.x;

         m_iMoveX = iMoveX;

      }

      if (iMoveX != 0)
      {

         int w = m_pgame->m_sizePage.cx;

         int iDelay = 84;

         int iDistance = m_iMoveX * 5 * ((get_tick_count() - m_dwLastChangeXDir) / iDelay);

         m_ptNow.x = m_ptStart.x + iDistance;

         while (m_ptNow.x < 0)
         {

            m_ptNow.x += w;

         }

         while (m_ptNow.x > w)
         {

            m_ptNow.x -= w;

         }


      }

   }



   void character::_001OnLButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);


   }

   void character::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);

   }

   void character::_001OnMouseMove(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      point pt = pmouse->m_pt;
   }
    
   void character::on_key_move_tick()
   {

      if (m_bLeft)
      {

         if (m_bRight)
         {

            moveX(0);

            return;

         }
         else
         {

            moveLeft();

            return;

         }

      }
      else if (m_bRight)
      {

         moveRight();

         return;

      }
      else
      {

         moveX(0);

      }

   }

   void character::on_move_tick(bool bEnd)
   {


      if (bEnd)
      {
         
         moveX(0);

         return;

      }

      point pt;

      Session.get_cursor_pos(pt);

      m_pgame->ScreenToClient(pt);

      rect r(m_ptNow, m_ts.m_il.m_size);

      if (pt.x > r.right)
      {

         moveRight();

      }
      else if (pt.x < r.left)
      {

         moveLeft();

      }
      else
      {

         moveX(0);

      }
      
   }

   bool character::get_rect(LPRECT lprect)
   {

      lprect->left = m_ptNow.x;
      lprect->top = m_ptNow.y;
      lprect->left = m_ptNow.x + m_ts.m_il.m_size.cx;
      lprect->top = m_ptNow.y + m_ts.m_il.m_size.cy;
      
      return true;

   }

   

   int character::hit_test(point pt)
   {

      rect r(m_ptNow, m_ts.m_il.m_size);

      if (r.contains(pt))
         return 0;
      else
         return -1;

   }


   bool character::canMoveLeft(bool bPlatformCall)
   {

      if (!bPlatformCall)
      {

         return m_pgame->canMoveLeft(m_iIndex, true);

      }
      else
      {

         return true;

      }

   }


   bool character::canMoveRight(bool bPlatformCall)
   {

      if (!bPlatformCall)
      {

         return m_pgame->canMoveRight(m_iIndex, true);

      }
      else
      {

         return true;

      }


   }


   bool character::canMoveUp(bool bPlatformCall)
   {

      if (!bPlatformCall)
      {

         return m_pgame->canMoveUp(m_iIndex, true);

      }
      else
      {

         return true;

      }


   }

   bool character::canMoveDown(bool bPlatformCall)
   {

      if (!bPlatformCall)
      {

         return m_pgame->canMoveDown(m_iIndex, true);

      }
      else
      {

         return true;

      }


   }

   void character::moveLeft()
   {

      moveX(-1);

   }


   void character::moveRight()
   {

      moveX(1);

   }


} // namespace estamira



