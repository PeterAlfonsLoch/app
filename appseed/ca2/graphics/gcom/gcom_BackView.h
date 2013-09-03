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
         virtual public signalizable
      {
      protected:


         int32_t                        m_iRefCount;

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
         Main(sp(base_application) papp, Interface * pbackviewinterface);
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
         ::draw2d::graphics & GetTransferDC();
         void SetBackgroundImageChangeInterval(uint32_t dwMillis);
         void OnImageLoaded(::draw2d::dib * pdib);
         void UpdateDrawingObjects();
         void OnDestroy();
         void OnResize();
         int32_t SetState(e_state estate);
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
         
         int32_t PulseEvent(e_event eevent);


         void DeferCheckLayout();


         virtual bool UpdateBuffer(LPCRECT lpcrect);
         
         
         virtual void OnAfterImageLoaded();

         
         virtual bool RenderBuffer();
         virtual bool LoadNextImage(bool bSynch);
         virtual bool IsFullScreen();



      };




   } // namespace backview

} // namespace gcom
