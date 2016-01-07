#pragma once


namespace user
{

   
   class combo_box;
   namespace wndfrm
   {
      namespace frame
      {
         class WorkSet;
      }
   }


   class CLASS_DECL_CORE combo_list : 
      virtual public ::user::control
   {
   public:


      bool                                m_bComboList;
      combo_box *                         m_pcombo;
      int32_t                             m_iItemHeight;
      int                                 m_iHover;
      int                                 m_iBorder;

      ::user::interaction *               m_puiDeactivateTogether;
      ::user::wndfrm::frame::WorkSet *    m_puiDeactivateTogetherSet;


      combo_list(::aura::application * papp);
      virtual ~combo_list();


      virtual void install_message_handling(::message::dispatch * pdispatch);


      virtual void _001OnDraw(::draw2d::graphics * pdc);

      virtual void _001OnDrawVerisimple(::draw2d::graphics * pdc);
      virtual void _001OnDrawSimply(::draw2d::graphics * pdc);

      virtual void _002OnDrawVerisimple(::draw2d::graphics * pdc);
      virtual void _002OnDrawSimply(::draw2d::graphics * pdc);

      virtual void query_full_size(LPSIZE lpsize) const;

      virtual int32_t _001GetItemHeight() const;

      bool pre_create_window(::user::create_struct & cs);


      using ::user::control::GetClientRect;
      virtual bool GetClientRect(RECT64 * lprect);


      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnMouseActivate);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMButtonDown);
      DECL_GEN_SIGNAL(_001OnRButtonDown);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      virtual index hit_test(point pt, e_element & eelement);


      virtual bool keyboard_focus_is_focusable();
      virtual bool keyboard_focus_OnKillFocus();


   };


} //  namespace user



