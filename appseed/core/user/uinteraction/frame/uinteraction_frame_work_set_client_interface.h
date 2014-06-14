#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class CLASS_DECL_CORE WorkSetClientInterface :
            virtual public database::user::interaction
         {
         public:


            WorkSet              m_workset;
            ::user::EAppearance      m_eappearanceBefore;


            WorkSetClientInterface();
            virtual ~WorkSetClientInterface();


            sp(::user::interaction) WfiGetWindow();


            virtual void _001OnDraw(::draw2d::graphics * pca);


            virtual void WfiEnableFullScreen(bool bEnable = true);
            virtual bool WfiIsFullScreen();
            virtual bool WfiIsFullScreenEnabled();


            virtual bool WfiClose();
            virtual bool WfiRestore(bool bForceNormal = false);
            virtual bool WfiMinimize();
            virtual bool WfiMaximize();
            virtual bool WfiFullScreen();
            virtual bool WfiUp();
            virtual bool WfiDown();
            virtual bool WfiNotifyIcon();


            virtual bool WfiOnBeginSizing(UINT nType, point pt);
            virtual bool WfiOnBeginMoving(point pt);
            virtual bool WfiOnSize(bool bTracking);
            virtual bool WfiOnMove(bool bTracking);


            virtual void WfiOnDown();
            virtual void WfiOnUp();
            virtual void WfiOnRestore();
            virtual void WfiOnMinimize();
            virtual void WfiOnMaximize();
            virtual void WfiOnFullScreen();
            virtual void WfiOnExitFullScreen();
            virtual void WfiOnClose();
            virtual void WfiOnNotifyIcon();
            virtual bool WfiOnBeforeDown();
            virtual bool WfiOnBeforeUp();
            virtual bool WfiOnBeforeRestore();
            virtual bool WfiOnBeforeMinimize();
            virtual bool WfiOnBeforeMaximize();
            virtual bool WfiOnBeforeClose();
            virtual bool WfiOnBeforeFullScreen();
            virtual bool WfiOnBeforeNotifyIcon();
            virtual void WfiOnAfterDown();
            virtual void WfiOnAfterUp();
            virtual void WfiOnAfterRestore();
            virtual void WfiOnAfterMinimize();
            virtual void WfiOnAfterMaximize();
            virtual void WfiOnAfterClose();
            virtual void WfiOnAfterFullScreen();
            virtual void WfiOnAfterNotifyIcon();



         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user








