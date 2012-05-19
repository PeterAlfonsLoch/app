#pragma once


namespace user
{

   class scroll_info
   {
   public:
      UINT     cbSize;
      UINT     fMask;
      int      nMin;
      int      nMax;
      int      nPage;
      int      nPos;
      int      nTrackPos;
   };

   class CLASS_DECL_ca2 scroll_bar :
      virtual public ::user::interaction
   {
   public:
      enum e_orientation
      {
         orientation_horizontal = 1,
         orientation_vertical = 2
      };

      e_orientation  m_eorientation;
      scroll_info    m_scrollinfo;
      bool           m_bTracking;


      scroll_bar();
      virtual ~scroll_bar();

      virtual int _001GetScrollPos() = 0;
      virtual int _001SetScrollPos(int iPos) = 0;
      virtual bool _001GetScrollInfo(scroll_info * psi) = 0;
      virtual bool _001SetScrollInfo(scroll_info * psi, bool bRedraw = true) = 0;


      using user::interaction::create;
      virtual bool create(e_orientation eorientation, DWORD dwStyle, rect & rect, ::user::interaction * pParentWnd, UINT nID);

      virtual void send_scroll_message(UINT nSBCode);

   };

} // namespace user
