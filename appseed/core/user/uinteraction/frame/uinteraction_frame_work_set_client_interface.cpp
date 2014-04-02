#include "framework.h"


namespace uinteraction
{



namespace frame
{


   WorkSetClientInterface::WorkSetClientInterface()
   {
      m_workset.set_app(m_pbaseapp);
   }

   WorkSetClientInterface::~WorkSetClientInterface()
   {

   }

   sp(::user::interaction) WorkSetClientInterface::WfiGetWindow()
   {
      return  (this);
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
      m_workset.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeClose())
         return false;
      WfiOnClose();
      WfiOnAfterClose();
      return true;
   }

   bool WorkSetClientInterface::WfiRestore()
   {
      m_workset.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeRestore())
         return false;
      WfiOnRestore();
      m_workset.SetAppearanceMode(AppearanceModeNormal);
      WfiOnAfterRestore();
      return true;
   }

   bool WorkSetClientInterface::WfiMaximize()
   {
      m_workset.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeMaximize())
         return false;
      WfiOnMaximize();
      m_workset.SetAppearanceMode(AppearanceModeZoomed);
      WfiOnAfterMaximize();
      return true;
   }

   bool WorkSetClientInterface::WfiFullScreen(bool bFullScreen, bool bRestore)
   {

      try
      {

         if(bFullScreen)
         {


            if(m_workset.IsFullScreen())
               return true;

            if(!m_workset.IsFullScreenEnabled())
               return false;

            if(m_workset.m_pappearance != NULL)
            {
            
               m_workset.m_pappearance->SetAutomaticModeSwitching(false);
            
               if(!WfiOnBeforeFullScreen(bFullScreen))
                  return false;
   
               m_eappearancemodeFullScreen = m_workset.GetAppearanceMode();

               m_workset.SetAppearanceMode(AppearanceModeFullScreen);

            }
         
            WfiOnFullScreen(bFullScreen);

            WfiOnAfterFullScreen(bFullScreen);
         
            if(m_workset.m_pappearance != NULL)
            {

               if(m_workset.get_appearance()->m_pworkset != NULL && m_workset.get_appearance()->m_pworkset->m_pframeschema != NULL)
               {
               
                  ASSERT(m_workset.get_appearance()->m_pworkset != NULL);

                  ASSERT(m_workset.get_appearance()->m_pworkset->m_pframeschema != NULL);

                  m_workset.get_appearance()->m_pworkset->m_pframeschema->on_appearance_mode_change();

               }

               m_workset.m_pappearance->SetAutomaticModeSwitching(true);

            }

            return true;
         }
         else
         {

            if(!m_workset.IsFullScreen())
               return true;

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
                  break;
               }
            }

            if(m_workset.GetAppearanceMode() != m_eappearancemodeFullScreen)
            {
               m_workset.SetAppearanceMode(m_eappearancemodeFullScreen);
            }

            m_eappearancemodeFullScreen = AppearanceModeFullScreen;

            return true;

         }

      }
      catch(...)
      {
      }

      return false;

   }

   bool WorkSetClientInterface::WfiNotifyIcon()
   {
      if(!m_workset.IsNotifyIconEnabled())
         return false;
      m_workset.m_pappearance->SetAutomaticModeSwitching(false);
      if(!WfiOnBeforeNotifyIcon())
         return false;
      WfiOnNotifyIcon();
      WfiOnAfterNotifyIcon();
      m_workset.m_pappearance->SetAutomaticModeSwitching(true);
      return true;
   }


   bool WorkSetClientInterface::WfiMinimize()
   {
      m_workset.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeMinimize())
         return false;
      WfiOnMinimize();
      m_workset.SetAppearanceMode(AppearanceModeIconic);
      WfiOnAfterMinimize();
      return true;
   }

   bool WorkSetClientInterface::WfiDown()
   {
      m_workset.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeDown())
         return false;
      WfiOnDown();
      WfiOnAfterDown();
      m_workset.m_pframeschema->title_bar_layout(false);
      return true;
   }

   bool WorkSetClientInterface::WfiUp()
   {
      m_workset.m_pappearance->SetAutomaticModeSwitching(true);
      if(!WfiOnBeforeUp())
         return false;
      WfiOnUp();
      WfiOnAfterUp();
      m_workset.m_pframeschema->title_bar_layout(false);
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
      if(m_workset.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }

   bool WorkSetClientInterface::WfiOnBeforeMinimize()
   {
      if(m_workset.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }

   bool WorkSetClientInterface::WfiOnBeforeRestore()
   {
      if(m_workset.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }

   bool WorkSetClientInterface::WfiOnBeforeUp()
   {
      if(m_workset.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }

   bool WorkSetClientInterface::WfiOnBeforeDown()
   {
      if(m_workset.IsFullScreen()
         && !WfiFullScreen(false, false))
         return false;
      return true;
   }


   void WorkSetClientInterface::WfiOnAfterClose()
   {

   }

   bool WorkSetClientInterface::WfiOnBeforeNotifyIcon()
   {
      if(!m_workset.IsNotifyIconEnabled())
         return false;
      return true;
   }


   void WorkSetClientInterface::WfiOnAfterFullScreen(bool bFullScreen)
   {
      if(bFullScreen)
      {
         m_workset.m_pframeschema->get_control_box()->ShowWindow(SW_HIDE);
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
      return m_workset.IsFullScreen();
   }

   bool WorkSetClientInterface::WfiIsFullScreenEnabled()
   {
      return m_workset.IsFullScreenEnabled();
   }


   void WorkSetClientInterface::WfiEnableFullScreen(bool bEnable)
   {
      m_workset.EnableFullScreen(bEnable);
   }

   void WorkSetClientInterface::_001OnDraw(::draw2d::graphics * pgraphics)
   {
      m_workset._001OnDraw(pgraphics);
   }


} // namespace frame






} // namespace uinteraction






