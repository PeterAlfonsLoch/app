#include "StdAfx.h"
#include "FrameSchema.h"

namespace window_frame
{

   WorkSetClientInterface::WorkSetClientInterface(::ca::application * papp) :
      ca(papp),
      m_wndframework(papp)
   {

   }

   WorkSetClientInterface::~WorkSetClientInterface()
   {

   }

   ::user::interaction* WorkSetClientInterface::WfiGetWindow()
   {
      return dynamic_cast < ::user::interaction * > (this);
   }

   void WorkSetClientInterface::WfiOnClose()
   {

   }

   void WorkSetClientInterface::WfiOnMaximize()
   {

   }

   void WorkSetClientInterface::WfiOnFullScreen(bool bFullScreen)
   {
      UNREFERENCED_PARAMETER(bFullScreen);
   }

   void WorkSetClientInterface::WfiOnNotifyIcon()
   {
   }

   void WorkSetClientInterface::WfiOnMinimize()
   {

   }

   void WorkSetClientInterface::WfiOnRestore()
   {

   }

   void WorkSetClientInterface::WfiOnUp()
   {

   }

   void WorkSetClientInterface::WfiOnDown()
   {

   }


   bool WorkSetClientInterface::WfiClose()
   {
      m_wndframework.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeClose())
         return false;
      WfiOnClose();
      WfiOnAfterClose();
      return true;
   }

   bool WorkSetClientInterface::WfiRestore()
   {
      m_wndframework.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeRestore())
         return false;
      WfiOnRestore();
      m_wndframework.SetAppearanceMode(AppearanceModeNormal);
      WfiOnAfterRestore();
      return true;
   }

   bool WorkSetClientInterface::WfiMaximize()
   {
      m_wndframework.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeMaximize())
         return false;
      WfiOnMaximize();
      m_wndframework.SetAppearanceMode(AppearanceModeZoomed);
      WfiOnAfterMaximize();
      return true;
   }

   bool WorkSetClientInterface::WfiFullScreen(bool bFullScreen, bool bRestore)
   {
      if(bFullScreen)
      {
         if(!m_wndframework.IsFullScreenEnabled())
            return false;
         m_wndframework.m_pappearance->SetAutomaticModeSwitching(false);
         if(!WfiOnBeforeFullScreen(bFullScreen))
            return false;
         m_eappearancemodeFullScreen = m_wndframework.GetAppearanceMode();
         m_wndframework.SetAppearanceMode(AppearanceModeFullScreen);
         WfiOnFullScreen(bFullScreen);
         WfiOnAfterFullScreen(bFullScreen);
         if(m_wndframework.GetAppearance()->m_pworkset != NULL
         && m_wndframework.GetAppearance()->m_pworkset->m_pframeschema != NULL)
         {
            ASSERT(m_wndframework.GetAppearance()->m_pworkset != NULL);
            ASSERT(m_wndframework.GetAppearance()->m_pworkset->m_pframeschema != NULL);
            m_wndframework.GetAppearance()->m_pworkset->m_pframeschema->OnAppearanceModeChange();
         }
         m_wndframework.m_pappearance->SetAutomaticModeSwitching(true);
         return true;
      }
      else
      {
         if(m_eappearancemodeFullScreen == AppearanceModeFullScreen)
         {
            m_eappearancemodeFullScreen = AppearanceModeNormal;
         }
         if(!WfiIsFullScreen())
            return true;
         WfiOnFullScreen(false);
         if(bRestore)
         {
            EAppearanceMode   eappearancemode = m_eappearancemodeFullScreen;

            switch(eappearancemode)
            {
            case AppearanceModeNormal:
               return WfiRestore();
            case AppearanceModeZoomed:
               return WfiMaximize();
            case AppearanceModeIconic:
               return WfiMinimize();
            default:
               // Not expected
               ASSERT(FALSE);
               break;
            }
         }
         m_eappearancemodeFullScreen = AppearanceModeFullScreen;
         return true;
      }
   }

   bool WorkSetClientInterface::WfiNotifyIcon()
   {
      if(!m_wndframework.IsNotifyIconEnabled())
         return false;
      m_wndframework.m_pappearance->SetAutomaticModeSwitching(false);
      if(!WfiOnBeforeNotifyIcon())
         return false;
      WfiOnNotifyIcon();
      WfiOnAfterNotifyIcon();
      m_wndframework.m_pappearance->SetAutomaticModeSwitching(true);
      return true;
   }


   bool WorkSetClientInterface::WfiMinimize()
   {
      m_wndframework.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeMinimize())
         return false;
      WfiOnMinimize();
      m_wndframework.SetAppearanceMode(AppearanceModeIconic);
      WfiOnAfterMinimize();
      return true;
   }

   bool WorkSetClientInterface::WfiDown()
   {
      m_wndframework.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeDown())
         return false;
      WfiOnDown();
      WfiOnAfterDown();
      m_wndframework.m_pframeschema->UpdateControlBox();
      return true;
   }

   bool WorkSetClientInterface::WfiUp()
   {
      m_wndframework.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeUp())
         return false;
      WfiOnUp();
      WfiOnAfterUp();
      m_wndframework.m_pframeschema->UpdateControlBox();
      return true;
   }


   bool WorkSetClientInterface::WfiOnBeforeClose()
   {
      return true;
   }


   bool WorkSetClientInterface::WfiOnBeforeFullScreen(bool bFullScreen)
   {
      UNREFERENCED_PARAMETER(bFullScreen);
      return true;
   }

   bool WorkSetClientInterface::WfiOnBeforeMaximize()
   {
      if(m_wndframework.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }

   bool WorkSetClientInterface::WfiOnBeforeMinimize()
   {
      if(m_wndframework.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }

   bool WorkSetClientInterface::WfiOnBeforeRestore()
   {
      if(m_wndframework.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }

   bool WorkSetClientInterface::WfiOnBeforeUp()
   {
      if(m_wndframework.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }

   bool WorkSetClientInterface::WfiOnBeforeDown()
   {
      if(m_wndframework.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }


   void WorkSetClientInterface::WfiOnAfterClose()
   {

   }

   bool WorkSetClientInterface::WfiOnBeforeNotifyIcon()
   {
      if(!m_wndframework.IsNotifyIconEnabled())
         return false;
      return true;
   }


   void WorkSetClientInterface::WfiOnAfterFullScreen(bool bFullScreen)
   {
      if(bFullScreen)
      {
         WindowDataSaveWindowRect();
      }
   }

   void WorkSetClientInterface::WfiOnAfterNotifyIcon()
   {
      WindowDataSaveWindowRect();
   }

   void WorkSetClientInterface::WfiOnAfterMaximize()
   {
      WindowDataSaveWindowRect();
   }

   void WorkSetClientInterface::WfiOnAfterMinimize()
   {
      WindowDataSaveWindowRect();
   }

   void WorkSetClientInterface::WfiOnAfterRestore()
   {
      WindowDataSaveWindowRect();
   }

   void WorkSetClientInterface::WfiOnAfterUp()
   {
      WindowDataSaveWindowRect();
   }

   void WorkSetClientInterface::WfiOnAfterDown()
   {
      WindowDataSaveWindowRect();
   }

   bool WorkSetClientInterface::WfiOnBeginMoving(point pt)
   {
      UNREFERENCED_PARAMETER(pt);
      return false;
   }

   bool WorkSetClientInterface::WfiOnBeginSizing(UINT nType, point pt)
   {
      UNREFERENCED_PARAMETER(nType);
      UNREFERENCED_PARAMETER(pt);
      return false;
   }

   bool WorkSetClientInterface::WfiOnMove(bool bTracking)
   {
      UNREFERENCED_PARAMETER(bTracking);
      return false;
   }

   bool WorkSetClientInterface::WfiOnSize(bool bTracking)
   {
      UNREFERENCED_PARAMETER(bTracking);
      return false;
   }

   bool WorkSetClientInterface::WfiIsFullScreen()
   {
      return m_wndframework.IsFullScreen();
   }

   bool WorkSetClientInterface::WfiIsFullScreenEnabled()
   {
      return m_wndframework.IsFullScreenEnabled();
   }


   void WorkSetClientInterface::WfiEnableFullScreen(bool bEnable)
   {
      m_wndframework.EnableFullScreen(bEnable);
   }

} // namespace window_frame




