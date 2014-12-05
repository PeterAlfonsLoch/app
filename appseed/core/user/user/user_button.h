#pragma once


namespace state
{

   enum e_state
   {
      unchecked,
      checked,
      tristate,
   };

   typedef flags < e_state > state;

} // namespace check


namespace user
{


   class CLASS_DECL_CORE button :
      virtual public control,
      virtual public elemental
   {
   public:

      enum e_style
      {
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
      istring                             m_istrButtonText;
      rect                                m_rectText;
      state::state                        m_state;
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

      ::draw2d::bitmap m_bitmap;          // not pressed default bitmap
      ::draw2d::bitmap m_bitmapSel;       // pressed bitmap
      ::draw2d::bitmap m_bitmapFocus;     // focus bitmap
      ::draw2d::bitmap m_bitmapDisabled;  // disabled bitmap
      ::draw2d::bitmap m_bitmapHover;     // hover bitmap


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

      void VirtualOnSize();

      virtual bool create_control(class control::descriptor * pdescriptor);

      visual::dib_sp          m_dib;


      virtual void ResizeToFit();



      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _001OnDraw(::draw2d::graphics * pdc);
      virtual void _002OnDraw(::draw2d::graphics * pdc);

      DECL_GEN_SIGNAL(_001OnCreate);
         virtual bool is_window_enabled();
      virtual bool enable_window(bool bEnable = true);
      virtual void _001SetCheck(check::e_check check, ::action::context actioncontext);
      virtual check::e_check _001GetCheck();
      virtual void _001SetState(state::state state, ::action::context actioncontext);
      virtual state::state _001GetState();

      virtual bool _001IsPressed();


      //      void _002OnDraw(::draw2d::graphics * pdc);

      virtual index get_hover();


      //      virtual void ResizeToFit();
      virtual void _001Layout();



      virtual index hit_test(point pt, e_element & eelement);

      //      virtual ::draw2d::font * _001GetFont();
      void _001SetButtonText(const char * lpcszText);
      void _001SetButtonTextId(const char * lpcszText);
      string _001GetButtonText();

      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(on_create);

      ::size calc_text_size();

      virtual bool keyboard_focus_is_focusable();

      virtual void pre_subclass_window();

      virtual void _001OnDrawSimple(::draw2d::graphics * pdc);

//      virtual void ResizeToFit();

      DECL_GEN_SIGNAL(_001OnCtlColor);
      DECL_GEN_SIGNAL(_001OnSetFocus);

#ifdef WINDOWS
      bool LoadBitmaps(UINT nIDBitmapResource,
         UINT nIDBitmapResourceSel = 0,
         UINT nIDBitmapResourceFocus = 0,
         UINT nIDBitmapResourceDisabled = 0,
         UINT nIDBitmapResourceHover = 0);
#endif

      bool LoadBitmaps(
         const char * lpszBitmapResource,
         const char * lpszBitmapResourceSel = NULL,
         const char * lpszBitmapResourceFocus = NULL,
         const char * lpszBitmapResourceDisabled = NULL,
         const char * lpszBitmapResourceHover = NULL);

      void UpdateHover();

      virtual void BaseToolTipGetRect(LPRECT lprect);
      virtual int32_t BaseToolTipGetIndex();

//      virtual void install_message_handling(::message::dispatch * pinterface);
#ifdef WINDOWSEX
      virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
#endif
      virtual void pre_translate_message(signal_details * pobj);
      virtual void message_handler(signal_details * pobj);

//      void ResizeToFit();
  //    virtual ~button();

//      DECL_GEN_SIGNAL(_001OnMouseMove);

//      virtual void install_message_handling(::message::dispatch * pinterface);

#ifdef WINDOWSEX
//      virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
#endif
      virtual bool pre_create_window(::user::create_struct& cs);

      void SetColorSchema(ColorSchema * pschema);
      void TransitionEffectStart();
      void TransitionEffectRunStep();
      bool IsPushed();
      void push(bool bPush = true);
      void Hover(bool bHover = true);
//      void UpdateHover();
      void _001OnDrawPush(::draw2d::graphics * pdc);

//      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnTimer);

   };


} // namespace user



