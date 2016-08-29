#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA character :
      virtual public ::signalizable
   {
   public:

      index                   m_iIndex;
      game *                  m_pgame;
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

      character(::aura::application * papp, index iIndex);
      virtual ~character();

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual bool init(string strTileMap, game * pgame);

      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);

      virtual void on_move_tick(bool bEnd = false);

      virtual void on_key_move_tick();

      virtual int hit_test(point pt);

      virtual void moveX(int iMoveX);

      virtual bool canMoveLeft(bool bPlatformCall = false);
      virtual bool canMoveRight(bool bPlatformCall = false);
      virtual bool canMoveUp(bool bPlatformCall = false);
      virtual bool canMoveDown(bool bPlatformCall = false);

      virtual bool get_rect(LPRECT lprect);
      virtual void moveLeft();
      virtual void moveRight();

   };


} // namespace estamira



