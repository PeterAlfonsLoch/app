#pragma once

namespace gcom
{
   namespace backview
   {
      
      class Main;
      class thread_dispatch;
      class load_image;

      class CLASS_DECL_ca thread : 
         virtual public ::radix::thread
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
            DWORD       m_dwCallbackThread;
         //   VARIANT varInfoHeader;
         //   VARIANT varBits;
         //   VARIANT varUserData;
            ::ax::bitmap     m_pbitmap;
            int         m_iUserData;
            int      cx;
            int      cy;
            mutex * m_lpcs;
         } STRETCHIMAGESTRUCTURE, *LPSTRETCHIMAGESTRUCTURE;

         typedef struct tagOnLoadImageStructure
         {
         //   const char *   m_lpImagePath;
         //   FIBITMAP *   m_pfiBitmap;
         //   HDC      m_hDCPersistent;
         //   HWND   m_hWndReturn;
         //   LPSTREAM * m_lpStreamEvents;
         //   DWORD   m_dwEventsCount;
         //   LPSTREAM m_lpStreamImageLoader;
         //   LPSTREAM m_lpStreamImageLoaderCP;
            ::ax::bitmap * m_pbitmap;

         } ONLOADIMAGESTRUCTURE, *LPONLOADIMAGESTRUCTURE;

         typedef struct tagOnStretchImageStructure
         {
         //   VARIANT varInfoHeader;
         //   VARIANT varBits;
         //   VARIANT varUserData;
            //HBITMAP      m_hBitmap;
            ::ax::bitmap *  m_pbitmap;
            int          m_cx;
            int          m_cy;
            int          m_iUserData;
         //   LPSTREAM * m_lpStreamEvents;
         //   DWORD   m_dwEventsCount;
         //   LPSTREAM m_lpStreamImageLoader;
         //   LPSTREAM m_lpStreamImageLoaderCP;

         } ONSTRETCHIMAGESTRUCTURE, *LPONSTRETCHIMAGESTRUCTURE;

         event                  m_evInitialized;
         mutex                     m_mutexBitmap;
         backview::Main   *          m_pbackviewinterface;   

         thread(::ax::application * papp);
         
         static const UINT MESSAGE_BACKVIEW;
         static const WPARAM WPARAM_BACKVIEW_IMAGELOADED;


         void SetMain(backview::Main * pmain);

         void install_message_handling(::gen::message::dispatch * pinterface);

          static DWORD WINAPI ThreadProcStretchImage(LPVOID lpParameter);
          static UINT AFX_CDECL ThreadProcLoadImage(LPVOID lpParameter);

         //void OnImageLoaded(HBITMAP hbitmap);
         long OnImageStretched(::ax::bitmap * pbitmap, long cx, long cy, long iUserData);

      //   ::ax::bitmap & GetBitmap();

         //void OnLyricViewSize(int iType);
         void LoadImageAsync(const load_image & loadimage);
         void StretchImageAsync(LPSTRETCHIMAGESTRUCTURE lpSi, bool bBitmapLocked);


         void PreTransitionImageAsync(backview::Main * pview);

         static UINT AFX_CDECL ThreadProcPreTransitionImage(LPVOID lpParameter);



         virtual bool initialize_instance();
         virtual int exit_instance();
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
         string               m_strImagePath;
         backview::Main *     m_pbackviewinterface;
         ::ax::bitmap_sp      m_pbitmap;
         gen::signal          m_signalImageLoaded;


         load_image(gcom::backview::thread * pbackviewthread, backview::Main * pbackviewinterface, const char * lpcwszImagePath);
         load_image(const load_image & loadimage);
         void OnImageLoaded();

      protected:
         


         load_image & operator =(const load_image & loadimage);
      };

      
   } // namespace backview

} // namespace gcom

