#pragma once

namespace user
{

   class menu_base;
   class menu_item;
   class menu_item_ptra;

   class CLASS_DECL_CORE menu_button_cmd_ui : public cmd_ui
   {
   public:


      menu_item_ptra *  m_pitema;
      menu_item *          m_pitemContainer;


      menu_button_cmd_ui(sp(::axis::application) papp);


      virtual void Enable(bool bOn, ::action::context actioncontext);
      virtual void _001SetCheck(check::e_check echeck, ::action::context actioncontext);
      virtual void SetText(const char * lpszText, ::action::context actioncontext);

   };



   class CLASS_DECL_CORE menu_button :
      public button
   {
   public:
      menu_button(sp(::axis::application) papp);
   public:
      virtual ~menu_button();

      menu_item *    m_pitem;
      rect                m_rectCheckBox;

      virtual void _001Layout();

      virtual void _001DrawCheck(::draw2d::graphics * pdc);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
   };

} // namespace user