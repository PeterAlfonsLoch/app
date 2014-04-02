#pragma once


namespace backview
{


   class CLASS_DECL_CORE Main :
      virtual public signalizable
   {
   public:



      int32_t                    m_iRefCount;

      bool                       m_bEnabled;
      e_state                    m_estate;
      Graphics *                 m_pgraphics;
      Interface *                m_pinterface;
      ImageChange *              m_pimagechange;
      TransitionEffect *         m_ptransitioneffect;
      VisualEffect *             m_pvisualeffect;

      thread *                   m_pthreadIdlePriority;
      thread *                   m_pthreadHighestPriority;
      bool                       m_bInitialized;
      ::mutex                    m_mutexStateMachine;

      bool                       m_bPendingLayout;


      Main(sp(base_application) papp, Interface * pbackviewinterface);
      virtual ~Main();


      void Shutdown();



      ::mutex & GetTransferMutex();
      ::draw2d::graphics_sp GetTransferDC();


      bool IsInitialized();
      void Enable(bool bEnable);
      bool IsEnabled();
      void GetCurrentImagePath(string & str);
      void SetCurrentImagePlacement(EImagePlacement eplacement);
      EImagePlacement GetCurrentImagePlacement();
      bool GetNextImagePath(string & str);
      void SetBackgroundImageChangeInterval(uint32_t dwMillis);
      void OnImageLoaded(::draw2d::dib * pdib);
      void update_drawing_objects();
      void OnDestroy();
      void OnResize();
      int32_t SetState(e_state estate);


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


      DECL_GEN_SIGNAL(_001OnImageLoaded);


   };


} // namespace backview










