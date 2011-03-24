#pragma once

namespace userbase
{

   class split_layout;

   class CLASS_DECL_ca split_bar :
      public ::user::interaction
   {
   public:
      split_bar(::ca::application * papp);

      int                     m_iIndex;
      split_layout *       m_pparent;
      HCURSOR                  m_hcursor;
      DWORD                   m_dwPosition;
      double                  m_dRate;
      double                  m_dMinimumRate;
      double                  m_dMaximumRate;

      void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

      virtual void _001OnDraw(::ca::graphics * pdc);
      BOOL create(split_layout * pparent);
      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
      virtual ~split_bar();

      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnLButtonDown)
      DECL_GEN_SIGNAL(_001OnLButtonUp)
      DECL_GEN_SIGNAL(_001OnMouseMove)

   };

} // namespace userbase