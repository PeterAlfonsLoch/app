#pragma once


namespace estamira
{


   class CLASS_DECL_ESTAMIRA game :
      virtual public ::aura::drawable,
      virtual public ::signalizable
   {
   public:

      ::user::interaction *         m_pui;
      int                           m_iMult;

      spa(character)                m_charactera;

      ::draw2d::dib_sp              m_dib;



      game(::aura::application * papp);
      virtual ~game();

      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::dib * pdib);

      virtual bool start(::user::interaction * pui);
      virtual void layout();

      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);

      virtual void remove_all_characters();

      virtual ::estamira::character * add_new_character(string strTileMap);

   };


} // namespace estamira



