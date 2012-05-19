#pragma once


namespace userbase
{

   class split_layout;

   class CLASS_DECL_ca2 split_bar :
      public ::user::interaction
   {
   public:


      int                     m_iIndex;
      split_layout *       m_pparent;
      HCURSOR                  m_hcursor;
      DWORD                   m_dwPosition;
      double                  m_dRate;
      double                  m_dMinimumRate;
      double                  m_dMaximumRate;
      DWORD                   m_dwMaxPosition;


      split_bar(::ca::application * papp);
      virtual ~split_bar();


      void install_message_handling(::gen::message::dispatch * pinterface);

      virtual void _001OnDraw(::ca::graphics * pdc);

      using ::user::interaction::create;
      bool create(split_layout * pparent);
      virtual bool pre_create_window(CREATESTRUCT& cs);

      
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)

      virtual void layout();

   };


} // namespace userbase


