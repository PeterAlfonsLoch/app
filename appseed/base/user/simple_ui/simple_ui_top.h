#pragma once



namespace simple_ui
{


   class top :
      virtual public ::simple_ui::interaction,
      virtual public ::simple_ui::style
   {
   public:


      bool                       m_bLButtonDown;
      POINT                      m_ptLButtonDown;
      POINT                      m_ptLButtonDownPos;

      bool                       m_bDrag;



      top(::aura::application * papp);
      virtual ~top();


      void install_message_handling(::message::dispatch * pdispatch) override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);


   };


} // namespace simple_ui




