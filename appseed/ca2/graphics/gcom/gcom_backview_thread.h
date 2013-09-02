#pragma once


namespace gcom
{


   namespace backview
   {


      class Main;
      class thread_dispatch;
      class load_image;


      class CLASS_DECL_ca2 thread : 
         virtual public ::ca2::thread
      {
      public:


         enum e_message
         {
            MessageCommand = WM_APP + 1,
         };

         enum ECommand
         {
            CommandPreTransitionImage,
            CommandLoadImage,
         };


         typedef struct tagStretchImageStructure
         {
            //    LPSTREAM    m_lpstrmCallback;
            uint32_t       m_dwCallbackThread;
            //   VARIANT varInfoHeader;
            //   VARIANT varBits;
            //   VARIANT varUserData;
            ::draw2d::bitmap     m_pbitmap;
            int32_t         m_iUserData;
            int32_t      cx;
            int32_t      cy;
            mutex * m_lpcs;
         } STRETCHIMAGESTRUCTURE, *LPSTRETCHIMAGESTRUCTURE;

         typedef struct tagOnLoadImageStructure
         {
            //   const char *   m_lpImagePath;
            //   FIBITMAP *   m_pfiBitmap;
            //   HDC      m_hDCPersistent;
            //   oswindow   m_oswindow_Return;
            //   LPSTREAM * m_lpStreamEvents;
            //   uint32_t   m_dwEventsCount;
            //   LPSTREAM m_lpStreamImageLoader;
            //   LPSTREAM m_lpStreamImageLoaderCP;
            ::draw2d::bitmap * m_pbitmap;

         } ONLOADIMAGESTRUCTURE, *LPONLOADIMAGESTRUCTURE;

         typedef struct tagOnStretchImageStructure
         {
            //   VARIANT varInfoHeader;
            //   VARIANT varBits;
            //   VARIANT varUserData;
            //HBITMAP      m_hBitmap;
            ::draw2d::bitmap *  m_pbitmap;
            int32_t          m_cx;
            int32_t          m_cy;
            int32_t          m_iUserData;
            //   LPSTREAM * m_lpStreamEvents;
            //   uint32_t   m_dwEventsCount;
            //   LPSTREAM m_lpStreamImageLoader;
            //   LPSTREAM m_lpStreamImageLoaderCP;

         } ONSTRETCHIMAGESTRUCTURE, *LPONSTRETCHIMAGESTRUCTURE;

         event                  m_evInitialized;
         mutex                     m_mutexBitmap;
         backview::Main   *          m_pbackviewinterface;   

         thread(sp(::application) papp);

         static const UINT MESSAGE_BACKVIEW;
         static const WPARAM WPARAM_BACKVIEW_IMAGELOADED;


         void SetMain(backview::Main * pmain);

         void install_message_handling(::ca2::message::dispatch * pinterface);

         static uint32_t ThreadProcStretchImage(void * lpParameter);
         static uint32_t ThreadProcLoadImage(void * lpParameter);

         //void OnImageLoaded(HBITMAP hbitmap);
         long OnImageStretched(::draw2d::bitmap * pbitmap, long cx, long cy, long iUserData);

         //   ::draw2d::bitmap & GetBitmap();

         //void OnLyricViewSize(int32_t iType);
         void LoadImageAsync(const load_image & loadimage);
         void StretchImageAsync(LPSTRETCHIMAGESTRUCTURE lpSi, bool bBitmapLocked);


         void PreTransitionImageAsync(backview::Main * pview);

         static UINT c_cdecl ThreadProcPreTransitionImage(LPVOID lpParameter);



         virtual bool initialize_instance();
         virtual int32_t exit_instance();
         virtual ~thread();

         DECL_GEN_SIGNAL(OnUserMessage)
            DECL_GEN_SIGNAL(OnBackViewMessage)
            DECL_GEN_SIGNAL(OnCommandMessage)

      };

      class thread_dispatch
      {
      public:
         thread_dispatch(thread * pbackviewthread);
         thread_dispatch & operator =(const thread_dispatch & dispatch);
         thread * GetThread();
         void PostBackViewThreadMessage(WPARAM wparam, LPARAM lparam);
      protected:
         thread * m_pbackviewthread;
      };

      class load_image :
         public thread_dispatch
      {
      public:


         string                  m_strImagePath;
         backview::Main *        m_pbackviewinterface;
         ::ca2::signal             m_signalImageLoaded;
         ::draw2d::dib *             m_pdib;


         load_image(::draw2d::dib * pdib, gcom::backview::thread * pbackviewthread, backview::Main * pbackviewinterface, const char * lpcwszImagePath);
         load_image(const load_image & loadimage);
         void OnImageLoaded();

      protected:



         load_image & operator =(const load_image & loadimage);
      };


   } // namespace backview

} // namespace gcom

