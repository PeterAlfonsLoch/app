#pragma once


namespace backview
{


   class CLASS_DECL_CORE thread :
      virtual public ::thread
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


      typedef struct tagOnLoadImageStructure
      {


         ::draw2d::bitmap_sp     m_spbitmap;


      } ONLOADIMAGESTRUCTURE, *LPONLOADIMAGESTRUCTURE;


      typedef struct tagOnStretchImageStructure
      {


         ::draw2d::bitmap_sp     m_spbitmap;
         int32_t                 m_cx;
         int32_t                 m_cy;
         int32_t                 m_iUserData;


      } ONSTRETCHIMAGESTRUCTURE, *LPONSTRETCHIMAGESTRUCTURE;

      event                      m_evInitialized;
      mutex                      m_mutexBitmap;
      backview::Main   *         m_pbackviewinterface;


      static const UINT MESSAGE_BACKVIEW;
      static const WPARAM WPARAM_BACKVIEW_IMAGELOADED;


      thread(sp(base_application) papp);
      virtual ~thread();


      virtual bool initialize_instance();
      virtual int32_t exit_instance();


      void SetMain(backview::Main * pmain);

      void install_message_handling(::message::dispatch * pinterface);

      static uint32_t ThreadProcStretchImage(void * lpParameter);
      static uint32_t ThreadProcLoadImage(void * lpParameter);

      //void OnImageLoaded(HBITMAP hbitmap);
      long OnImageStretched(::draw2d::bitmap * pbitmap, long cx, long cy, long iUserData);

      //   ::draw2d::bitmap & GetBitmap();

      //void OnLyricViewSize(int32_t iType);
      void LoadImageAsync(const load_image & loadimage);
      void StretchImageAsync(LPONSTRETCHIMAGESTRUCTURE lpSi, bool bBitmapLocked);


      void PreTransitionImageAsync(backview::Main * pview);

      static UINT c_cdecl ThreadProcPreTransitionImage(LPVOID lpParameter);




      DECL_GEN_SIGNAL(OnUserMessage);
      DECL_GEN_SIGNAL(OnBackViewMessage);
      DECL_GEN_SIGNAL(OnCommandMessage);

   };


   class thread_dispatch
   {
   public:


      thread * m_pbackviewthread;


      thread_dispatch(thread * pbackviewthread);
      thread_dispatch & operator =(const thread_dispatch & dispatch);


      thread * GetThread();
      void PostBackViewThreadMessage(WPARAM wparam, LPARAM lparam);


   };

   class load_image :
      public thread_dispatch
   {
   public:


      string                     m_strImagePath;
      backview::Main *           m_pbackviewinterface;
      class ::signal             m_signalImageLoaded;
      ::draw2d::dib_sp           m_spdib;


      load_image(::draw2d::dib * pdib, ::backview::thread * pbackviewthread, backview::Main * pbackviewinterface, const char * lpcwszImagePath);
      load_image(const load_image & loadimage);


      void OnImageLoaded();

      load_image & operator =(const load_image & loadimage);


   };


} // namespace backview





