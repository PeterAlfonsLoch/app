#pragma once


namespace userbase
{

   class split_layout;

   class CLASS_DECL_ca split_bar :
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


      split_bar(::ax::application * papp);
      virtual ~split_bar();


      void install_message_handling(::gen::message::dispatch * pinterface);

      virtual void _001OnDraw(::ax::graphics * pdc);

      using ::user::interaction::create;
      BOOL create(split_layout * pparent);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)


   };


} // namespace userbase


