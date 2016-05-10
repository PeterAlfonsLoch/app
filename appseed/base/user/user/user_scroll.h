#pragma once


namespace user
{


   class scroll_bar;


   class CLASS_DECL_BASE scroll_data
   {
   public:


      LONG        m_iPage;
      LONG        m_iLine;
      bool        m_bScroll;
      int32_t     m_iWidth;
      bool        m_bScrollEnable;


   };


   class CLASS_DECL_BASE scroll_x :
      virtual public interaction
   {
   public:


      sp(scroll_bar)    m_pscrollbarHorz;
      scroll_data       m_scrolldataHorz;


      scroll_x();
      virtual ~scroll_x();


      virtual void install_message_handling(::message::dispatch * pinterface);



      virtual void GetScrollRect(LPRECT lprect);
      virtual void on_change_view_size();
      virtual void on_change_viewport_offset();
      virtual void create_x_scroll_bar(const RECT & rect);
      virtual void layout_scroll_bar();
      virtual void _001DeferCreateXScrollBar();
      virtual void _001OnDeferCreateXScrollBar();
      virtual void _001ConstrainXScrollPosition();


      DECL_GEN_SIGNAL(_001OnHScroll);

      virtual int get_final_x_scroll_bar_width();

   };























   class CLASS_DECL_BASE scroll_y :
      virtual public interaction
   {
   public:


      sp(scroll_bar)       m_pscrollbarVert;
      scroll_data          m_scrolldataVert;
      int16_t              m_iWheelDelta;


      scroll_y();
      virtual ~scroll_y();


      virtual void install_message_handling(::message::dispatch * pinterface);


      virtual void GetScrollRect(LPRECT lprect);
      virtual void on_change_view_size();
      virtual void on_change_viewport_offset();
      virtual int32_t get_wheel_scroll_delta();
      virtual void create_y_scroll_bar(const RECT & rect);
      virtual void layout_scroll_bar();
      virtual void _001DeferCreateYScrollBar();
      virtual void _001OnDeferCreateYScrollBar();
      virtual void _001ConstrainYScrollPosition();


      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnMouseWheel);


      virtual int get_final_y_scroll_bar_width();


   };

   class CLASS_DECL_BASE scroll :
      virtual public ::user::scroll_x,
      virtual public ::user::scroll_y
   {
   public:


      ::size            m_sizeTotal;


      scroll();
      scroll(::aura::application * papp);
      virtual ~scroll();


      void on_change_view_size();
      void on_change_viewport_offset();
      void layout_scroll_bar();

      virtual void install_message_handling(::message::dispatch * pinterface);


      void GetScrollRect(LPRECT lprect);

      virtual ::size get_total_size();

   };


} // namespace user
























