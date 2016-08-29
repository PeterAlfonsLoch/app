#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA game :
      virtual public ::aura::drawable,
      virtual public ::signalizable,
      virtual public timer_callback
   {
   public:


      ::user::interaction *         m_pui;
      int                           m_iMult;

      spa(character)                m_charactera;

      ::draw2d::dib_sp              m_dibPage;

      uint32_t                      m_uiCursorDelay;
      uint32_t                      m_dwLastCursor;

      int                           m_iCurChar;
      timer                         m_timer;

      // Beam Mode is when the touched/mouse position points to exact instantaneous 
      // position of player. 
      // Beam Mode off moves the player according to tick, current player position
      // and relative touched/dragged cursor position.
      bool                          m_bBeamMode;

      // If keypulse is on, the key events are generated as PC mode.
      // If keypulse is off, arrow key press is treated as continuous movement force.
      bool                          m_bKeyPulse;

      point                         m_ptOffset;

      size                          m_sizePage;

      game(::aura::application * papp);
      virtual ~game();

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual bool start(::user::interaction * pui);
      virtual void layout();

      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      virtual void moveLeft(index iChar);

      virtual void moveRight(index iChar);

      virtual void remove_all_characters();

      virtual ::estamira::character * add_new_character(string strTileMap);

      virtual bool get_char_rect(LPRECT lprect, index iChar, bool bPlatformCall = false);

      virtual int hit_test(point pt);

      virtual bool on_timer(timer * ptimer);

      virtual void ScreenToClient(LPPOINT lppoint);

      virtual void on_move_tick();

      virtual bool canMoveUp(int iChar, bool bPlatformCall = false);
      virtual bool canMoveDown(int iChar, bool bPlatformCall = false);
      virtual bool canMoveLeft(int iChar, bool bPlatformCall = false);
      virtual bool canMoveRight(int iChar, bool bPlatformCall = false);

   };


} // namespace estamira



