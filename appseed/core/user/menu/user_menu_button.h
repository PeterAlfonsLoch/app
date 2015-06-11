#pragma once


namespace user
{


   class CLASS_DECL_CORE menu_button_cmd_ui : public cmd_ui
   {
   public:


      menu_item_ptra *  m_pitema;
      menu_item *          m_pitemContainer;


      menu_button_cmd_ui(::aura::application * papp);


      virtual void Enable(bool bOn, ::action::context actioncontext);
      virtual void _001SetCheck(check::e_check echeck, ::action::context actioncontext);
      virtual void SetText(const char * lpszText, ::action::context actioncontext);

   };



   class CLASS_DECL_CORE menu_button :
      virtual public button
   {
   public:
      
      
      
      menu_item *             m_pitem;
      rect                    m_rectCheckBox;

      menu_button(::aura::application * papp);
      virtual ~menu_button();

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void layout();

      virtual void _001DrawCheck(::draw2d::graphics * pdc);

      virtual void _001OnDraw(::draw2d::graphics * pdc);

      DECL_GEN_SIGNAL(_001OnMouseMove);


   };


} // namespace user







