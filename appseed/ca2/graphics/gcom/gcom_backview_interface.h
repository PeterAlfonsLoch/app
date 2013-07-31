#pragma once


namespace gcom
{


   class thread;


   namespace backview
   {


      class Main;


      namespace user
      {


         class interaction;


      } // namespace user


      class CLASS_DECL_ca2 Interface :
         virtual public ::ca2::signalizable
      {
      public:


         enum e_message
         {
            MessageBackView = WM_APP + 1359,
            MessageBackViewDequeue = WM_APP + 3377,
         };

         enum EBackViewWparam
         {
            BackViewWparamImageChangeEvent,
            BackViewWparamUpdateScreenRect,
            BackViewWparamUpdateScreenBaseRectArray,
         };



         Main *               m_pmain;
         bool                 m_bTransferVoid;
         uint32_t                m_dwTimerStep;


         ::ca2::file_set_sp     m_spfilesetBackgroundImage;



         Interface(sp(::ca2::application) papp);
         virtual ~Interface();

         void Shutdown();

         void install_message_handling(::ca2::message::dispatch * pinterface);

         virtual COLORREF GetBackgroundColor();
         void BackViewRender(::draw2d::graphics * pdc, int32_t x, int32_t y, int32_t w, int32_t h);
         void BackViewRender(::draw2d::graphics * pdc, LPCRECT lpcrect);
         void Enable(bool bEnable);
         bool IsEnabled();
         void GetCurrentImagePath(string & str);
         void SetCurrentImagePlacement(EImagePlacement eplacement);
         EImagePlacement GetCurrentImagePlacement();
         ::mutex & GetTransferMutex();
         ::draw2d::graphics & GetTransferDC();
         void SetBackgroundImageChangeInterval(uint32_t dwMillis);
         Main & GetMain();
         void OnImageLoaded(::draw2d::dib * pdib);
         void UpdateDrawingObjects();
         void OnDestroy();


         virtual void initialize_user_interaction();

         thread *     GetIdleThread();
         thread *     GetHighestThread();

         virtual void BackViewFeedback(::draw2d::graphics * pdc);
         virtual void BackViewGetClientRect(LPRECT lprect);
         virtual void BackViewClientToScreen(LPRECT lprect);
         virtual void BackViewPostMessage(UINT uiMessage, WPARAM wparam, LPARAM lparam);
         virtual void BackViewPostMessage(WPARAM wparam, LPARAM lparam);
         virtual void BackViewUpdateScreen();
         virtual void BackViewGetData(InterfaceData & data) = 0;
         virtual void BackViewSetData(InterfaceData & data) = 0;
         virtual void BackViewUpdateScreen(LPCRECT lpcrect, UINT uiRedraw);
         virtual void BackViewUpdateScreen(rect_array & recta, UINT uiRedraw);

         virtual string BackViewGetNextBackgroundImagePath();
         virtual void BackViewSetCurrentBackgroundImagePath(const char * psz);

         virtual bool BackViewGetDestroy();
         virtual bool BackViewGetImagePlacement(const char * lpcsz, EImagePlacement & eplacement);

         virtual HENHMETAFILE BackViewGetFillingMetaFile();

         virtual void ImageChangePostEvent(e_event eevent);
         virtual bool UpdateBuffer(LPCRECT lpcrect);

         virtual void OnAfterImageLoaded();

         virtual sp(::user::interaction) BackViewGetInteraction();


         virtual bool RenderBuffer();
         virtual bool LoadNextImage(bool bSynch);
         virtual bool IsFullScreen();


         // Windows message handler
         DECL_GEN_VSIGNAL(OnBackViewMessage)
         DECL_GEN_VSIGNAL(OnDequeueMessage)
         DECL_GEN_VSIGNAL(OnWndSize)
         DECL_GEN_VSIGNAL(OnWndTimer)
         DECL_GEN_VSIGNAL(OnWndCreate)


      };


   } // namespace backview


} // namespace gcom


