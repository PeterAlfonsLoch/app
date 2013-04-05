#pragma once

namespace userbase
{

   class menu_base;
   class menu_item;
   class menu_item_ptra;

   class CLASS_DECL_ca2 menu_button_cmd_ui : public cmd_ui
   {
   public:


      menu_item_ptra *  m_pitema;
      menu_item *          m_pitemContainer;


      menu_button_cmd_ui(::ca::applicationsp papp);


      virtual void Enable(bool bOn);
      virtual void SetCheck(check::e_check echeck);
      virtual void SetText(const char * lpszText);

   };



   class CLASS_DECL_ca2 menu_button :
      public button
   {
   public:
      menu_button(::ca::applicationsp papp);
   public:
      virtual ~menu_button();

      menu_item *    m_pitem;
      rect                m_rectCheckBox;

      virtual void _001Layout();

      virtual void _001DrawCheck(::ca::graphics * pdc);

      virtual void _001OnDraw(::ca::graphics * pdc);
   };

} // namespace userbase