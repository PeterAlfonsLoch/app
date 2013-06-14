#pragma once

namespace uinteraction
{


namespace frame
{

   class WorkSet;

   class CLASS_DECL_ca2 MoveManager :
      virtual public ::ca2::signalizable
   {
      friend class WorkSet;
   public:
      enum EBorder
      {
         BorderNone = 0,
         BorderTop = 1,
         BorderRight = 2,
         BorderBottom = 4,
         BorderLeft = 8,
         BorderAll = BorderTop | BorderRight | BorderBottom   | BorderLeft,
      };

   protected:
      WorkSet *            m_pworkset;
      uint32_t                m_dwLastMoveTime;
      bool                 m_bPendingMove;
      point                m_ptPendingMove;
      void *                 m_oswindowPendingMove;
      EBorder              m_eborderMask;
      point                m_ptCursorOrigin;
      point                m_ptWindowOrigin;
      bool                 m_bMoving;
      uint32_t                m_dwLastMovingTime;
      UINT                 m_uiSWPFlags;
      uint32_t                m_dwPaintDelay;
   public:

      MoveManager(WorkSet * pworkset);
      virtual ~MoveManager();


      sp(::user::interaction) GetEventWindow();
      sp(::user::interaction) GetMoveWindow();

      bool Relay(::ca2::message::mouse * pmouse);
      bool _000OnLButtonDown(::ca2::message::mouse * pmouse);
      bool _000OnMouseMove(::ca2::message::mouse * pmouse);
      bool _000OnLButtonUp(::ca2::message::mouse * pmouse);
      bool _000OnTimer(UINT nIDEvent);


      void SetBorderMask(EBorder emask);
      EBorder GetBorderMask();

      bool IsMoving();
      void MoveWindow(void * oswindow, point pt);
      void SetSWPFlags(UINT uiFlags);
      bool relay_event(MESSAGE * lpMsg);
      bool update(WorkSet * pwf);

      static const uint32_t s_dwMoveTime;

      void message_handler(sp(::user::interaction) pwnd, ::ca2::signal_object * pobj);
   };

} // namespace frame






} // namespace uinteraction






