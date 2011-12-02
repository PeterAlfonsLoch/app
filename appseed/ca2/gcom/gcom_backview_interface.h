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

      class CLASS_DECL_ca Interface :
         virtual public gen::signalizable
      {

      public:
         bool m_bTransferVoid;
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



         DWORD                m_dwTimerStep;

      protected:
         Main *               m_pmain;

      public:
         ex2::file_set_sp m_spfilesetBackgroundImage;

         Interface(::ax::application * papp);
         virtual ~Interface();

         void Shutdown();

         void install_message_handling(::gen::message::dispatch * pinterface);

         virtual COLORREF GetBackgroundColor();
         void BackViewRender(::ax::graphics * pdc, int x, int y, int w, int h);
         void BackViewRender(::ax::graphics * pdc, LPCRECT lpcrect);
         void Enable(bool bEnable);
         bool IsEnabled();
         void GetCurrentImagePath(string & str);
         void SetCurrentImagePlacement(EImagePlacement eplacement);
         EImagePlacement GetCurrentImagePlacement();
         ::mutex & GetTransferMutex();
         ::ax::graphics & GetTransferDC();
         void SetBackgroundImageChangeInterval(DWORD dwMillis);
         Main & GetMain();
         void OnImageLoaded(::ax::bitmap * pbitmap);
         void UpdateDrawingObjects();
         void OnDestroy();


         virtual void initialize_user_interaction();

         thread *     GetIdleThread();
         thread *     GetHighestThread();

         virtual void BackViewFeedback(::ax::graphics * pdc);
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

         virtual user::interaction * BackViewGetInteraction();

         
         virtual bool RenderBuffer();
         virtual bool LoadNextImage(bool bSynch);
         virtual bool IsFullScreen();

         //virtual bool _000WndProc(UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult);
         //virtual bool RelayWndProc(LPMSG lpmsg);
         virtual bool RelayWndProc(UINT message, WPARAM wparam, LPARAM lparam);

         // Windows message handler
         DECL_GEN_VSIGNAL(OnBackViewMessage)
         DECL_GEN_VSIGNAL(OnDequeueMessage)
         DECL_GEN_VSIGNAL(OnWndSize)
         DECL_GEN_VSIGNAL(OnWndTimer)
         DECL_GEN_VSIGNAL(OnWndCreate)
      };

   } // namespace backview

} // namespace gcom
