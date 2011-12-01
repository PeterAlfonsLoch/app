#pragma once

namespace window_frame
{

   class WorkSet;

   class CLASS_DECL_ca MoveManager :
      virtual public gen::signalizable
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
      DWORD                m_dwLastMoveTime;
      bool                 m_bPendingMove;
      point                m_ptPendingMove;
      HWND                 m_hwndPendingMove;
      EBorder              m_eborderMask;
      point                m_ptCursorOrigin;
      point                m_ptWindowOrigin;
      bool                 m_bMoving;
      DWORD                m_dwLastMovingTime;
      UINT                 m_uiSWPFlags;
      DWORD                m_dwPaintDelay;
   public:
      
      MoveManager(WorkSet * pworkset);
      virtual ~MoveManager();


      ::user::interaction * GetEventWindow();
      ::user::interaction * GetMoveWindow();

      bool Relay(gen::message::mouse * pmouse);
      bool _000OnLButtonDown(::gen::message::mouse * pmouse);
      bool _000OnMouseMove(::gen::message::mouse * pmouse);
      bool _000OnLButtonUp(::gen::message::mouse * pmouse);
      bool _000OnTimer(UINT nIDEvent);


      void SetBorderMask(EBorder emask);
      EBorder GetBorderMask();

      bool IsMoving();
      void MoveWindow(HWND hwnd, point pt);
      void SetSWPFlags(UINT uiFlags);
      bool relay_event(MSG * lpMsg);
      bool update(WorkSet * pwf);

      static const DWORD s_dwMoveTime;
      
      void message_handler(::user::interaction * pwnd, gen::signal_object * pobj);
   };

} // namespace window_frame

