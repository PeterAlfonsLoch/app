#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class CLASS_DECL_CORE SizeManager :
            virtual public signalizable
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
            uint32_t                m_dwLastSizingTime;
            UINT                 m_uiSWPFlags;
            EGrip                  m_egripMask;
            uint32_t                m_dwPaintDelay;
            int32_t                  m_iPaintCount;
         public:
            SizeManager(WorkSet * pworkset);
            virtual ~SizeManager();

            EHitTest hit_test(point ptCursor);
            //void _000InstallEventHandling(iguimessage::MessageDispatch * pdispatch);

            bool _000OnLButtonDown(::message::mouse * pmouse);
            bool _000OnMouseMove(::message::mouse * pmouse);
            bool _000OnLButtonUp(::message::mouse * pmouse);

            bool Relay(::message::mouse * pmouse);

            void NotifyFramework(EHitTest emode);
            EGrip EModeToEGrip(EHitTest emode);
            EGrip GetGripMask();
            void SetGripMask(EGrip egrip);
            bool IsSizing();
            void SetSWPFlags(UINT uiFlags);
            void SetMinSize(size size);
            ::visual::e_cursor translate(EHitTest ehittest);
            bool update(WorkSet * pset);

            sp(::user::interaction) GetSizingWindow();
            sp(::user::interaction) GetEventWindow();


            void SizeWindow(sp(::user::interaction) pwnd, point pt, bool bTracking);
            void MoveWindow(sp(::user::interaction) pwnd, LPCRECT lpcrect);

            void message_handler(sp(::user::interaction) pwnd, signal_details * pobj);
         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user






