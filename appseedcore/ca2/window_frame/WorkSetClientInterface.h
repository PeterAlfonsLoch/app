#pragma once


namespace window_frame 
{

   class CLASS_DECL_ca WorkSetClientInterface :
      virtual public database::user::interaction
   {
      

   protected:
      virtual void WfiOnDown();
      virtual void WfiOnUp();
      virtual void WfiOnRestore();
      virtual void WfiOnMinimize();
      virtual void WfiOnMaximize();
      virtual void WfiOnFullScreen(bool bFullScreen);
      virtual void WfiOnClose();
      virtual void WfiOnNotifyIcon();
      virtual bool WfiOnBeforeDown();
      virtual bool WfiOnBeforeUp();
      virtual bool WfiOnBeforeRestore();
      virtual bool WfiOnBeforeMinimize();
      virtual bool WfiOnBeforeMaximize();
      virtual bool WfiOnBeforeClose();
      virtual bool WfiOnBeforeFullScreen(bool bFullScreen);
      virtual bool WfiOnBeforeNotifyIcon();
      virtual void WfiOnAfterDown();
      virtual void WfiOnAfterUp();
      virtual void WfiOnAfterRestore();
      virtual void WfiOnAfterMinimize();
      virtual void WfiOnAfterMaximize();
      virtual void WfiOnAfterClose();
      virtual void WfiOnAfterFullScreen(bool bFullScreen);
      virtual void WfiOnAfterNotifyIcon();
      ::user::interaction* WfiGetWindow();
      WorkSetClientInterface(::ca::application * papp);
      virtual ~WorkSetClientInterface();

   public:
      WorkSet            m_wndframework;
      EAppearanceMode   m_eappearancemodeFullScreen;

   public:
      void WfiEnableFullScreen(bool bEnable = true);
      virtual bool WfiIsFullScreen();
      virtual bool WfiIsFullScreenEnabled();
      virtual bool WfiOnBeginSizing(UINT nType, point pt);
      virtual bool WfiOnBeginMoving(point pt);
      virtual bool WfiOnSize(bool bTracking);
      virtual bool WfiOnMove(bool bTracking);
      
      virtual bool WfiClose();
      virtual bool WfiRestore();
      virtual bool WfiMinimize();
      virtual bool WfiMaximize();
      virtual bool WfiFullScreen(bool bFullScreen, bool bRestore);
      virtual bool WfiUp();
      virtual bool WfiDown();
      virtual bool WfiNotifyIcon();
   };

} // namespace window_frame
