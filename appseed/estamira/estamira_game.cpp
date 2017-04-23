#include "framework.h"


namespace estamira
{

   game::game(::aura::application * papp) :
      object(papp),
      m_dibPage(allocer()),
      m_timer(papp,23)
   {

      m_uiCursorDelay = 100;

      m_bKeyPulse = false;
      m_bBeamMode = false;

      m_ptOffset = null_point();

      defer_create_mutex();
      m_iMult = 4;
      m_iCurChar = -1;

      m_timer.m_pcallback = this;
      m_timer.m_nIDEvent = 23;
      m_timer.m_pmutex = m_pmutex;
   }

   game::~game()
   {

   }

   void game::install_message_handling(::message::dispatch * pdispatch)
   {
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pdispatch, this, &game::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pdispatch, this, &game::_001OnKeyUp);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pdispatch, this, &game::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pdispatch, this, &game::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pdispatch, this, &game::_001OnMouseMove);

   }


   bool game::start(::user::interaction * pui)
   {

      m_pui = pui;

      install_message_handling(pui->m_pimpl);

      m_timer.start(23, true);

      return true;

   }

   void game::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      m_pui->GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;

      sp(::draw2d::dib) pdib = m_dibPage;

      int w = pdib->m_size.cx;

      if (w <= 0)
         return;

      int h = pdib->m_size.cy;

      if (h <= 0)
         return;

      pdib->Fill(0);

      for (auto & p : m_charactera)
      {

         p->_001OnDraw(pdib->get_graphics());

      }



      pgraphics->SetStretchBltMode(0);
      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
      pgraphics->StretchBlt(0, 0, rectClient.width(), rectClient.height(), pdib->get_graphics(), 0, 0, pdib->m_size.cx, pdib->m_size.cy, SRCCOPY);


   }



   void game::remove_all_characters()
   {
      
      m_charactera.remove_all();

   }

   ::estamira::character * game::add_new_character(string strTileMap)
   {

      sp(::estamira::character) pcharacter = canew(::estamira::character(get_app(), m_charactera.get_count()));

      pcharacter->init(strTileMap, this);

      m_charactera.add(pcharacter);

      return pcharacter;

   }

   void game::on_layout()
   {
    
      rect rectClient;

      m_pui->GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;
      
      m_sizePage.cx = rectClient.width() / MAX(1, m_iMult);
      m_sizePage.cy = rectClient.height() / MAX(1, m_iMult);
      
      m_dibPage->create(m_sizePage);


   }


   void game::_001OnKeyDown(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);
   
   }

   void game::_001OnKeyUp(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);


   }



   void game::_001OnLButtonDown(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      point pt = pmouse->m_pt;

      

      ScreenToClient(pt);

      if (m_charactera.get_count() <= 0)
      {
         m_iCurChar = 0;
      }
      else
      {
         m_iCurChar = hit_test(pt);
      }
      if (m_iCurChar >= 0)
      {
         on_move_tick();
         m_pui->SetCapture();
      }

      pmouse->m_bRet = true;

   }

   void game::_001OnLButtonUp(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);
      m_iCurChar = -1;
      m_pui->ReleaseCapture();
      if (m_iCurChar >= 0 && m_iCurChar < m_charactera.get_count())
      {

         m_charactera[m_iCurChar]->on_move_tick(true);

      }

      pmouse->m_bRet = true;
   }

   void game::_001OnMouseMove(signal_details * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);

      if (m_iCurChar >= 0 && m_iCurChar < m_charactera.get_count())
      {

         //m_charactera[m_iCurChar]->_001OnMouseMove(pobj);

      }

      pmouse->m_bRet = true;
   }

   int game::hit_test(point pt)
   {

      int i = 0;

      for (auto & c : m_charactera)
      {


         if (c->hit_test(pt) >= 0)
         {

            if (0)
            {
               string str;


               str = "Clicked in character " + string((char)( 'a' + i));

               Application.simple_message_box(NULL, str);

            }
            return i;
         }

         i++;

      }


      return -1;

   }

   void game::ScreenToClient(LPPOINT lppoint)
   {

      lppoint->x -= m_ptOffset.x;
      lppoint->y -= m_ptOffset.y;

      m_pui->ScreenToClient(lppoint);

      rect rectClient;

      m_pui->GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;

      ::draw2d::dib_sp pdib = m_dibPage;

      if (pdib->area() <= 0)
         return;
      
      lppoint->x = lppoint->x * pdib->m_size.cx / rectClient.width();
      lppoint->y = lppoint->y * pdib->m_size.cy / rectClient.height();


   }

   bool game::on_timer(timer * ptimer)
   {

      if (ptimer->m_nIDEvent == 23)
      {
         on_move_tick();
      }
      return true;
   }
   
   
   void game::on_move_tick()
   {

      if (get_tick_count() - m_dwLastCursor < m_uiCursorDelay)
      {

         return;

      }

      m_dwLastCursor = get_tick_count();

      if (m_iCurChar >= 0)
      {

         if (m_iCurChar < m_charactera.get_count())
         {

            m_charactera[m_iCurChar]->on_move_tick();

         }
         else
         {

            point pt;

            Session.get_cursor_pos(pt);

            ScreenToClient(pt);

            rect r;

            get_char_rect(r, m_iCurChar);

            if (pt.x > r.right)
            {

               moveRight(0);

            }
            else if (pt.x < r.left)
            {

               moveLeft(0);

            }

         }

      }
      else
      {

         for (auto & c : m_charactera)
         {

            c->on_key_move_tick();

         }

      }

   }


   bool game::canMoveUp(int iChar, bool bPlatformCall)
   {

      if (!bPlatformCall)
      {

         return m_charactera[iChar]->canMoveUp(true);

      }
      else
      {

         return true;

      }

   }


   bool game::canMoveDown(int iChar, bool bPlatformCall)
   {

      if (!bPlatformCall)
      {

         return m_charactera[iChar]->canMoveDown(true);

      }
      else
      {

         return true;

      }

   }


   bool game::canMoveLeft(int iChar, bool bPlatformCall)
   {

      if (!bPlatformCall)
      {

         return m_charactera[iChar]->canMoveLeft(true);

      }
      else
      {

         return true;

      }

   }


   bool game::canMoveRight(int iChar, bool bPlatformCall)
   {

      if (!bPlatformCall)
      {

         return m_charactera[iChar]->canMoveRight(true);

      }
      else
      {

         return true;

      }

   }

   void game::moveLeft(index iChar)
   {

   }

   void game::moveRight(index iChar)
   {

   }


   bool game::get_char_rect(LPRECT lprect, index iChar, bool bPlatformCall)
   {

      if (!bPlatformCall)
      {

         return m_charactera[iChar]->get_rect(lprect);

      }
      else
      {

         return false;

      }

   }


} // namespace estamira



