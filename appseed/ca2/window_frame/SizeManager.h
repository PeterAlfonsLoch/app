#pragma once

namespace window_frame
{

   class WorkSet;

   class CLASS_DECL_ca SizeManager :
      virtual public ::gen::signalizable   
   {
      friend class WorkSet;
   protected:
      WorkSet *            m_pworkset;
      ::critical_section   m_cs;
      EHitTest             m_ehittestMode;
      EHitTest             m_ehittestCursor;
      point                m_ptCursorOrigin;
      rect                 m_rcWindowOrigin;
      size                 m_minSize;
      size                 m_minBorder;
      DWORD                m_dwLastSizingTime;
      UINT                 m_uiSWPFlags;
      EGrip                  m_egripMask;
      DWORD                m_dwPaintDelay;
      int                  m_iPaintCount;
   public:
      SizeManager(WorkSet * pworkset);
      virtual ~SizeManager();

      EHitTest hit_test(point ptCursor);
      //void _000InstallEventHandling(iguimessage::MessageDispatch * pdispatch);

      bool _000OnLButtonDown(::user::win::message::mouse * pmouse);
      bool _000OnMouseMove(::user::win::message::mouse * pmouse);
      bool _000OnLButtonUp(::user::win::message::mouse * pmouse);

      bool Relay(::user::win::message::mouse * pmouse);

      void NotifyFramework(EHitTest emode);
      EGrip EModeToEGrip(EHitTest emode);
      EGrip GetGripMask();
      void SetGripMask(EGrip egrip);
      bool IsSizing();
      void SetSWPFlags(UINT uiFlags);
      void SetMinSize(size size);
      ::visual::e_cursor translate(EHitTest ehittest);
      bool update(WorkSet * pset);

      ::user::interaction* GetSizingWindow();
      ::user::interaction* GetEventWindow();


      void SizeWindow(::user::interaction * pwnd, point pt, bool bTracking);
      void MoveWindow(::user::interaction * pwnd, LPCRECT lpcrect);

      void message_handler(::user::interaction * pwnd, gen::signal_object * pobj);
   };

} // namespace window_frame
