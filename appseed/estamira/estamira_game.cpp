#include "framework.h"


namespace estamira
{

   game::game(::aura::application * papp) :
      object(papp),
      m_dib(allocer())
   {

      m_iMult = 4;

   }

   game::~game()
   {

   }

   void game::install_message_handling(::message::dispatch * pdispatch)
   {
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pdispatch, this, &game::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pdispatch, this, &game::_001OnKeyUp);

   }


   bool game::start(::user::interaction * pui)
   {

      m_pui = pui;

      install_message_handling(pui->m_pimpl);

      return true;

   }

   void game::_001OnDraw(::draw2d::dib * pdib)
   {

      rect rectClient;

      m_pui->GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;

      int w = m_dib->m_size.cx;

      if (w <= 0)
         return;

      int h = m_dib->m_size.cy;

      if (h <= 0)
         return;

      m_dib->Fill(0);

      for (auto & p : m_charactera)
      {

         p->_001OnDraw(m_dib);

      }



      pdib->get_graphics()->SetStretchBltMode(0);
      pdib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
      pdib->get_graphics()->StretchBlt(0, 0, rectClient.width(), rectClient.height(), m_dib->get_graphics(), 0, 0, m_dib->m_size.cx, m_dib->m_size.cy, SRCCOPY);


   }



   void game::remove_all_characters()
   {
      
      m_charactera.remove_all();

   }

   ::estamira::character * game::add_new_character(string strTileMap)
   {

      sp(::estamira::character) pcharacter = canew(::estamira::character(get_app()));

      pcharacter->init(strTileMap, m_pui);

      m_charactera.add(pcharacter);

      return pcharacter;

   }

   void game::layout()
   {
    
      rect rectClient;

      m_pui->GetClientRect(rectClient);

      if (rectClient.area() <= 0)
         return;

      m_dib->create(rectClient.width() / MAX(1, m_iMult), rectClient.height() / MAX(1, m_iMult));

   }


   void game::_001OnKeyDown(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);
   
   }

   void game::_001OnKeyUp(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);


   }

} // namespace estamira



