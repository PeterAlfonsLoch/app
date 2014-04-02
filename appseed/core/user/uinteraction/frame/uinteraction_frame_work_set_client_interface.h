#pragma once

namespace uinteraction
{



namespace frame 
{


   class CLASS_DECL_CORE WorkSetClientInterface :
      virtual public database::user::interaction
   {
   public:

      
      WorkSet              m_workset;
      EAppearanceMode      m_eappearancemodeFullScreen;
      

      WorkSetClientInterface();
      virtual ~WorkSetClientInterface();


      sp(::user::interaction) WfiGetWindow();


      virtual void _001OnDraw(::draw2d::graphics * pca);


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



   };


} // namespace frame







} // namespace uinteraction






