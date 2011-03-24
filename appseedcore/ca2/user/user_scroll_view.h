#pragma once

namespace user
{

   class scroll_bar;

   class CLASS_DECL_ca scroll_view :
      virtual public control
   {
   public:
      class scroll_info
      {
      public:
         rect        m_rectMargin;
         point       m_ptScroll;
         size        m_sizeTotal;
         size        m_sizePage;
         size        m_sizeLine;
         size        m_sizeClient;
         bool        m_bVScroll;   
         bool        m_bHScroll;
         int         m_iScrollHeight;
         int         m_iScrollWidth;
      };

      scroll_bar * m_pscrollbarHorz;
      scroll_bar * m_pscrollbarVert;
      scroll_info m_scrollinfo;

      scroll_view(::ca::application * papp);
      virtual ~scroll_view();


      void LayoutScrollBars();

      virtual void GetClientRect(LPRECT lprect);

      


      virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);



      void _001GetScrollInfo(scroll_info & info);

      void _001UpdateScrollBars();



      void send_scroll_message(::user::win::message::scroll * pscroll);

      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnVScroll)
      DECL_GEN_SIGNAL(_001OnHScroll)
      DECL_GEN_SIGNAL(_001OnUser9654)
   };

} // namespace user