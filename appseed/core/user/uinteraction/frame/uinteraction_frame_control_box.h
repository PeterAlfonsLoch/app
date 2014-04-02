#pragma once



namespace uinteraction
{


   namespace frame
   {


      class  CLASS_DECL_CORE control_box :
         virtual public ::user::interaction
      {
      public:

         WorkSet *                     m_pworkset;
         DWORD                         m_dwShowTime;
         bool                          m_bShowAttempt;
         bool                          m_bDrag;
         point                         m_ptDrag;
         int32_t                       m_iButtonMargin;
         int32_t                       m_iButtonSize;
         ::draw2d::font_sp             m_fontMarlett;

         ::draw2d::brush_sp            m_brushButtonBack;
         ::draw2d::brush_sp            m_brushButtonBackSel;
         ::draw2d::brush_sp            m_brushButtonBackFocus;
         ::draw2d::brush_sp            m_brushButtonBackDisabled;

         ::draw2d::pen_sp              m_penButtonBack;
         ::draw2d::pen_sp              m_penButtonBackSel;
         ::draw2d::pen_sp              m_penButtonBackFocus;
         ::draw2d::pen_sp              m_penButtonBackDisabled;

         COLORREF                      m_crButtonFore;
         COLORREF                      m_crButtonForeSel;
         COLORREF                      m_crButtonForeFocus;
         COLORREF                      m_crButtonForeDisabled;


         map < e_button, e_button, id, id >           m_mapButtonId;
         map < id, id, e_button, e_button >           m_mapIdButton;
         map < e_button, e_button, bool, bool >       m_buttonmapPresent;


         map < e_button, e_button, sp(control_box_button), sp(control_box_button) >      m_buttonmap;


         control_box(sp(base_application) papp);
         virtual ~control_box();


         virtual void set_button_color_system_default_001();


         virtual void install_message_handling(::message::dispatch *pinterface);


         void drag(point pt);


         DECL_GEN_SIGNAL(_001OnShowWindow);
         DECL_GEN_SIGNAL(_001OnLButtonDown);
         DECL_GEN_SIGNAL(_001OnLButtonUp);
         DECL_GEN_SIGNAL(_001OnMouseMove);
         DECL_GEN_SIGNAL(_001OnTimer);
         DECL_GEN_SIGNAL(_001OnCreate);
         DECL_GEN_SIGNAL(_001OnMove);
         DECL_GEN_SIGNAL(_001OnSize);

         virtual void layout();

         virtual int32_t calc_button_size();

         virtual int32_t calc_control_box_height();

         virtual int32_t calc_control_box_normal_width();

         virtual int32_t calc_control_box_zoomed_width();

         virtual int32_t calc_control_box_full_screen_width();

         ::uinteraction::frame::appearance * get_appearance();

         virtual void reset_layout();

         virtual int32_t get_button_margin();

         virtual bool has_button(e_button ebutton);
         virtual void hide_button(e_button ebutton, bool bHide = true);
         virtual int32_t get_button_size();
         virtual bool create_buttons();
         virtual void update_control_box_button(e_button ebutton);
         virtual void update_control_box_buttons();
         virtual bool create_button(e_button ebutton);
         virtual bool get_control_box_button_caption(e_button ebutton, string & str);
         virtual void set_control_box_button_id(e_button ebutton, id id);
         virtual id get_control_box_button_id(e_button ebutton);
         virtual e_button get_control_box_button_type(id id);
         sp(control_box_button) get_button(e_button ebutton);
         virtual sp(::uinteraction::frame::control_box_button) get_box_button(e_button ebutton);


      };


   } // namespace frame


} // namespace uinteraction




