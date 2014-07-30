#pragma once


namespace user
{

   class scroll_info
   {
   public:
      UINT     cbSize;
      UINT     fMask;
      int32_t      nMin;
      int32_t      nMax;
      int32_t      nPage;
      int32_t      nPos;
      int32_t      nTrackPos;
   };

   class CLASS_DECL_BASE scroll_bar :
      virtual public ::user::control
   {
   public:

      e_orientation  m_eorientation;
      scroll_info    m_scrollinfo;
      bool           m_bTracking;


      scroll_bar();
      virtual ~scroll_bar();

      virtual int32_t _001GetScrollPos() = 0;
      virtual int32_t _001SetScrollPos(int32_t iPos) = 0;
      virtual bool _001GetScrollInfo(scroll_info * psi) = 0;
      virtual bool _001SetScrollInfo(scroll_info * psi, bool bRedraw = true) = 0;


      using ::user::interaction::create;
      virtual bool create(e_orientation eorientation, uint32_t dwStyle, rect & rect, sp(::user::interaction) pParentWnd, UINT nID);

      virtual void send_scroll_message(UINT nSBCode);

      virtual point get_parent_scroll_position();
      virtual point get_ascendant_scroll_position();


   };

} // namespace user
