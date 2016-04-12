#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA character :
      virtual public ::signalizable
   {
   public:

      ::user::interaction *   m_pui;
      string                  m_strTileMap;
      int                     m_iMoveX;
      bool                    m_bLeft;
      bool                    m_bRight;
      point                   m_pt;
      point                   m_ptStart;
      point                   m_ptNow;
      DWORD                   m_dwLastChangeXDir;
      DWORD                   m_dwLastUp;
      DWORD                   m_dwUpTime;

      string                  m_strJumpSound;
      string                  m_strWalkSound;

      ::user::e_key           m_ekeyLeft;
      ::user::e_key           m_ekeyUp;
      ::user::e_key           m_ekeyRight;



      //sp(::multimedia::sound_track)      m_psound;

      ::estamira::tileset           m_ts;

      character(::aura::application * papp);
      virtual ~character();

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::dib * pdib);

      virtual bool init(string strTileMap, ::user::interaction * pui);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      virtual void update_movex();


   };


} // namespace estamira



