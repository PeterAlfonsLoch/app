#pragma once


namespace user
{


   class CLASS_DECL_APP_CORE_ATARI800 font_list:
      virtual public control,
      virtual public ::data::listener
   {
   public:

      int                  m_iSel;
      int                  m_iHover;
      stringa              m_straNameEnum;
      stringa              m_straName;
      stringa              m_straFontEnum;
      stringa              m_straFont;
      spa(::draw2d::font)  m_fonta;
      string               m_strText;
      string               m_strTextLayout;
      rect                 m_rectMargin;
      rect_array           m_recta;


      font_list();
      font_list(::aura::application * papp);
      virtual ~font_list();

      void font_list_common_construct();

      //virtual void assert_valid() const;
      //virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_handling(::message::dispatch * pdispatch);

      virtual void _001OnDraw(::draw2d::graphics * pdc);

      virtual void on_update(::user::impact * pSender,LPARAM lHint,object* pHint);


      string      get_cur_sel_face_name();
      int         get_cur_sel();


      DECL_GEN_SIGNAL(_001OnCreate);

      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnMouseMove);

      int hit_test(point pt);

      virtual void update();

      virtual void layout();

      bool set_sel_by_name(string str);

   };


   typedef ::user::show < ::user::scroll < ::user::font_list > > font_list_view;


} // namespace user





















