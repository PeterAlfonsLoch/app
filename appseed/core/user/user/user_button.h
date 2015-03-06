#pragma once


namespace user
{


   class CLASS_DECL_CORE button :
      virtual public control
   {
   public:

      enum e_style
      {
         style_none,
         style_normal,
         style_simple,
         style_bitmap,
         style_push,
         style_list
      };

      class bitmap
      {
      public:

         ::visual::dib_sp                    m_dib;          // not pressed default bitmap
         ::visual::dib_sp                    m_dibSel;       // pressed bitmap
         ::visual::dib_sp                    m_dibFocus;     // focus bitmap
         ::visual::dib_sp                    m_dibDisabled;  // disabled bitmap
         ::visual::dib_sp                    m_dibHover;     // hover bitmap

      };


      class list
      {
      public:

         sp(image_list)                      m_pimagelistNormal;
         sp(image_list)                      m_pimagelistItemHover;
         sp(image_list)                      m_pimagelistSubItemHover;
         int32_t                             m_iImageNormal;
         int32_t                             m_iImageItemHover;
         int32_t                             m_iImageSubItemHover;

      };

      //normal

      e_style                             m_estyle;
      check::e_check                      m_echeck;
      rect                                m_rectText;
      index                               m_iClick;
      ::user::front_end_schema::button *  m_pschema;
      ::user::front_end_schema::button *  m_pschemaDraw;
      e_stock_icon                        m_estockicon;


      // bitmap

      bitmap *                            m_pbitmap;

      list *                              m_plist;
      //bool                                m_bActionHover;




      button(::aura::application * papp);
      virtual ~button();

      virtual bool create_control(class control::descriptor * pdescriptor);

      virtual void ResizeToFit();

      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001OnDrawPush(::draw2d::graphics * pdc);
      virtual void _001OnDrawList(::draw2d::graphics * pdc);
      virtual void _001OnDrawBitmap(::draw2d::graphics * pdc);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void _002OnDraw(::draw2d::graphics * pdc);

      virtual bool is_custom_draw();

      virtual void _001SetCheck(check::e_check check, ::action::context actioncontext);
      virtual check::e_check _001GetCheck();

      virtual bool is_pressed();


      virtual index hit_test(point pt, e_element & eelement);

      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnCreate);


      ::size calc_text_size();

      virtual bool keyboard_focus_is_focusable();

      virtual bool has_action_hover(); 

      bool LoadBitmaps(::var var,::var varSel = ::var::type_null,::var varFocus = ::var::type_null,::var varDisabled = ::var::type_null,::var varHover = ::var::type_null);


      virtual void set_button_style(e_style estyle);
      virtual void on_enter_button_style(e_style estyle);
      virtual void on_exit_button_style(e_style estyle);

      virtual void BaseToolTipRelayEvent(signal_details * pobj);
      virtual void BaseToolTipGetRect(LPRECT lprect);
      virtual int32_t BaseToolTipGetIndex();

      virtual void pre_translate_message(signal_details * pobj);


      virtual void layout();


      virtual void set_stock_icon(e_stock_icon eicon);
      virtual e_stock_icon get_stock_icon();

   };


} // namespace user



