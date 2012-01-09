#pragma once

namespace gcom
{
   namespace backview
   {
      class Graphics;
      class ImageChange;
      class TransitionEffect;
      class VisualEffect;
      class Interface;
      class thread;

      class CLASS_DECL_ca2 Main :
         virtual public gen::signalizable
      {
      protected:


         int                        m_iRefCount;

         bool                       m_bEnabled;
         e_state                     m_estate;
         Graphics *                  m_pgraphics;
         Interface *                m_pinterface;
         ImageChange *               m_pimagechange;
         TransitionEffect *         m_ptransitioneffect;
         VisualEffect *             m_pvisualeffect;
         
         thread *                   m_pthreadIdlePriority;
         thread *                    m_pthreadHighestPriority;
         bool                        m_bInitialized;
         ::mutex                     m_mutexStateMachine;

      public:

         bool                       m_bPendingLayout;

      public:
         Main(::ca::application * papp, Interface * pbackviewinterface);
         virtual ~Main();

         void AddRef();
         void Release();
         void Shutdown();

         

         bool IsInitialized();
         void Enable(bool bEnable);
         bool IsEnabled();
         void GetCurrentImagePath(string & str);
         void SetCurrentImagePlacement(EImagePlacement eplacement);
         EImagePlacement GetCurrentImagePlacement();
         bool GetNextImagePath(string & str);
         ::mutex & GetTransferMutex();
         ::ca::graphics & GetTransferDC();
         void SetBackgroundImageChangeInterval(DWORD dwMillis);
         void OnImageLoaded(::ca::dib * pdib);
         void UpdateDrawingObjects();
         void OnDestroy();
         void OnResize();
         int SetState(e_state estate);
         //void RunTransitionEffectStep();
         DECL_GEN_SIGNAL(_001OnImageLoaded);

         Interface & GetInterface();
         ImageChange & GetImageChange();
         TransitionEffect & GetTransitionEffect();
         Graphics & GetGraphics();
         VisualEffect & GetVisualEffect();
         thread * GetIdleThread();
         thread * GetHighestThread();

         void OnDequeueMessage(WPARAM wparam, LPARAM lparam);

         virtual void ImageChangePostEvent(e_event eevent);
         
         int PulseEvent(e_event eevent);


         void DeferCheckLayout();


         virtual bool UpdateBuffer(LPCRECT lpcrect);
         
         
         virtual void OnAfterImageLoaded();

         
         virtual bool RenderBuffer();
         virtual bool LoadNextImage(bool bSynch);
         virtual bool IsFullScreen();



      };




   } // namespace backview

} // namespace gcom
