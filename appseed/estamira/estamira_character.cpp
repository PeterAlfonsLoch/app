#include "framework.h"


namespace estamira
{

   character::character(::aura::application * papp) :
      object(papp),
      m_ts(papp)
   {
      m_dwUpTime = 1000;
      m_bLeft = false;
      m_bRight = false;

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

   }


   bool character::init(string strTileMap, ::user::interaction * pui)
   {

      m_pui = pui;

      install_message_handling(pui->m_pimpl);

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

   void character::_001OnDraw(::draw2d::dib * pdib)
   {

      int w = pdib->m_size.cx;

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

      int iDistance = m_iMoveX * 5 * ((get_tick_count() - m_dwLastChangeXDir) / iDelay);

      while (m_ptStart.x + m_pt.x + iDistance < 0)
      {
         iDistance += w;
      }
      while (m_ptStart.x + m_pt.x + iDistance > w)
      {
         iDistance -= w;
      }
      m_ptNow.x = m_ptStart.x + m_pt.x + iDistance;
      int iUp = 0;
      int iUpMax = 48;
      if (get_tick_count() - m_dwLastUp < m_dwUpTime)
      {
         iUp = iUpMax * sin(3.1415 * double(get_tick_count() - m_dwLastUp) / double(m_dwUpTime));
      }
      m_ptNow.y = m_ptStart.y + m_pt.y - iUp;
      pdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
      m_ts.draw(pdib, stra[((get_tick_count() - m_dwLastChangeXDir) / iDelay) % stra.get_size()], m_ptNow.x, m_ptNow.y);

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
         m_bLeft = true;
         update_movex();
      }
      else if (pkey->m_ekey == m_ekeyRight)
      {
         m_bRight = true;
         update_movex();
      }

   }

   void character::_001OnKeyUp(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);
    
      if (pkey->m_ekey == m_ekeyLeft)
      {
         m_bLeft = false;
         update_movex();
      }
      else if (pkey->m_ekey == m_ekeyRight)
      {
         m_bRight = false;
         update_movex();
      }

   }

   void character::update_movex()
   {
      int iMoveX;
      if (m_bLeft)
      {
         if (m_bRight)
         {
            iMoveX = 0;
         }
         else
         {
            iMoveX = -1;
         }
      }
      else if (m_bRight)
      {
         iMoveX = 1;

      }
      else
      {
         iMoveX = 0;
      }
      if (m_iMoveX != iMoveX)
      {
         m_iMoveX = iMoveX;
         m_ptStart = m_ptNow;
         m_dwLastChangeXDir = ::get_tick_count();
      }
   }


} // namespace estamira



