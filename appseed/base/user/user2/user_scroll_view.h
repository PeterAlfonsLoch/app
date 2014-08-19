#pragma once


namespace user
{


   class scroll_bar;


   class CLASS_DECL_BASE scroll_view :
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
         int32_t         m_iScrollHeight;
         int32_t         m_iScrollWidth;
         bool        m_bVScrollBarEnable;
         bool        m_bHScrollBarEnable;
      };


      sp(scroll_bar)    m_pscrollbarHorz;
      sp(scroll_bar)    m_pscrollbarVert;
      scroll_info       m_scrollinfo;

      int16_t             m_iWheelDelta;





      scroll_view(sp(::axis::application) papp);
      virtual ~scroll_view();


      virtual void _001LayoutScrollBars();

      virtual void _001DeferCreateScrollBars();
      virtual void _001OnDeferCreateScrollBars();
      static  UINT c_cdecl thread_proc_defer_create_scroll_bars(LPVOID lpparam);

      virtual void GetClientRect(LPRECT lprect);

      
      virtual void create_scroll_bar(const RECT & rect, e_orientation eorientation);


      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual int32_t get_wheel_scroll_delta();

      void _001GetScrollInfo(scroll_info & info);

      void _001UpdateScrollBars();


      virtual void _001GetViewRect(LPRECT lprect);
      virtual void _001GetViewClientRect(LPRECT lprect);
      virtual void SetScrollSizes();


      void send_scroll_message(::message::scroll * pscroll);


      virtual void _001OnUpdateScrollPosition();


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnMouseWheel);
      DECL_GEN_SIGNAL(_001OnUser9654);

      
      virtual point get_scroll_position();


   };


} // namespace user

