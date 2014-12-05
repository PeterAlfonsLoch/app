#pragma once


namespace user
{


   class CLASS_DECL_CORE button :
      virtual public control,
      virtual public elemental
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

      //normal

      e_style                             m_estyle;
      check::e_check                      m_echeck;
      bool                                m_bEnabled;
      //istring                             m_istrButtonText;
      rect                                m_rectText;
      index                               m_iClick;
      ::user::front_end_schema::button *  m_pschema;
      ::user::front_end_schema::button *  m_pschemaDraw;
      bool                                m_bLButtonDown;

      // simple 

      bool                 m_bTransparent;
      ::draw2d::brush_sp       m_brushBkg;
      bool                 m_bFocus;


      // bitmap
      bool  m_bHover;            // set if cursor is over the button
      bool  m_bCommandEnable;    // set if command is enabled

      ::visual::dib_sp     m_dib;          // not pressed default bitmap
      ::visual::dib_sp     m_dibSel;       // pressed bitmap
      ::visual::dib_sp     m_dibFocus;     // focus bitmap
      ::visual::dib_sp     m_dibDisabled;  // disabled bitmap
      ::visual::dib_sp     m_dibHover;     // hover bitmap


      //list

      sp(image_list)      m_pimagelistNormal;
      sp(image_list)      m_pimagelistItemHover;
      sp(image_list)      m_pimagelistSubItemHover;
      int32_t               m_iImageNormal;
      int32_t               m_iImageItemHover;
      int32_t               m_iImageSubItemHover;


      // push
      class CLASS_DECL_CORE ColorSchema
      {
      public:
         color::hls   m_hlsRateHover;
         color::hls   m_hlsRatePush;
      };

      //COLORREF       m_crPush;
      //COLORREF       m_crPushHover;
      //COLORREF       m_crNormal;
      //COLORREF       m_crHover;
      COLORREF         m_cr; // Normal color

//      bool             m_bHover;
      bool             m_bPush;
      bool             m_bTransitionEffect;
      index            m_iStepCount;
      index            m_iStep;

      ColorSchema *    m_pcolorschema;



      button(::aura::application * papp);
      virtual ~button();

      //void VirtualOnSize();

      virtual bool create_control(class control::descriptor * pdescriptor);

      virtual void ResizeToFit();



      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001OnDrawPush(::draw2d::graphics * pdc);
      virtual void _001OnDrawList(::draw2d::graphics * pdc);
      virtual void _001OnDrawBitmap(::draw2d::graphics * pdc);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void _002OnDraw(::draw2d::graphics * pdc);

      DECL_GEN_SIGNAL(_001OnCreate);
         virtual bool is_window_enabled();
      virtual bool enable_window(bool bEnable = true);
      virtual void _001SetCheck(check::e_check check, ::action::context actioncontext);
      virtual check::e_check _001GetCheck();
//      virtual void _001SetState(state::state state, ::action::context actioncontext);
  //    virtual state::state _001GetState();

      virtual bool is_pressed();


      //      void _002OnDraw(::draw2d::graphics * pdc);

      virtual index get_hover();




      virtual index hit_test(point pt, e_element & eelement);

      //      virtual ::draw2d::font * _001GetFont();
      //void _001SetButtonText(const char * lpcszText);
      //void _001SetButtonTextId(const char * lpcszText);
      //string _001GetButtonText();

      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(on_create);

      ::size calc_text_size();

      virtual bool keyboard_focus_is_focusable();

      virtual void pre_subclass_window();

      //virtual void _001OnDrawSimple(::draw2d::graphics * pdc);

//      virtual void ResizeToFit();

      DECL_GEN_SIGNAL(_001OnCtlColor);
      DECL_GEN_SIGNAL(_001OnSetFocus);

      bool LoadBitmaps(::var var,::var varSel = ::var::type_null,::var varFocus = ::var::type_null,::var varDisabled = ::var::type_null,::var varHover = ::var::type_null);


      virtual void set_button_style(e_style estyle);
      virtual void on_enter_button_style(e_style estyle);
      virtual void on_exit_button_style(e_style estyle);

      virtual void BaseToolTipRelayEvent(signal_details * pobj);
      virtual void BaseToolTipGetRect(LPRECT lprect);
      virtual int32_t BaseToolTipGetIndex();

      virtual void pre_translate_message(signal_details * pobj);
      virtual void message_handler(signal_details * pobj);


//      virtual bool pre_create_window(::user::create_struct& cs);

      void SetColorSchema(ColorSchema * pschema);
      void TransitionEffectStart();
      void TransitionEffectRunStep();
      bool is_pushed();
      void push(bool bPush = true);
      void Hover(bool bHover = true);

//      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnTimer);

      virtual void layout();

   };


} // namespace user



