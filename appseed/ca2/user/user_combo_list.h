#pragma once


namespace user
{

   
   class combo_box;


   class CLASS_DECL_ca2 combo_list : 
      virtual public ::user::control
   {
   public:


      combo_box *    m_pcombo;
      int            m_iItemHeight;


      combo_list();
      virtual ~combo_list();


      virtual void install_message_handling(::gen::message::dispatch * pdispatch);


      virtual void _001OnDraw(::ca::graphics * pdc);


      virtual void query_full_size(LPSIZE lpsize) const;

      virtual int _001GetItemHeight() const;

      const char * GetIconWndClass(DWORD dwDefaultStyle, const char * pszMatter);


      bool pre_create_window(CREATESTRUCT & cs);


      DECL_GEN_SIGNAL(_001OnKillFocus);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnMouseActivate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnMButtonDown);
      DECL_GEN_SIGNAL(_001OnRButtonDown);


      virtual index hit_test(point pt, e_element & eelement);


   };


} //  namespace user



