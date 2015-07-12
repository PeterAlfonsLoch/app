#pragma once


namespace metrowin
{


   ref class directx_application : 
      public Windows::ApplicationModel::Core::IFrameworkView,
      public ::axis::system_window
   {
   internal:


      Windows::Foundation::Point m_ptLastCursor;

      String ^ m_strId;

      Agile<Windows::UI::Core::CoreWindow>  m_window;

      directx_base ^                         m_directx;
      
      bool  m_bFontopusShift;

      mutex m_mutex;

      ::base::system * m_psystem;
      ::base::application * m_papp;

      bool        m_bLeftButton;
      bool        m_bMiddleButton;
      bool        m_bRightButton;

      Windows::Foundation::Rect m_rectLastWindowRect;

      ::aura::application * get_app() const
      {
         return m_papp;
      }


      directx_application(::base::system * psystem,String ^ strId);


      void init_part_2ex();
      void install_message_handling_2ex();
      ::user::window_draw * create_twf_2ex();

      // DirectXBase Methods
      //virtual void CreateDeviceIndependentResources() override;
      //virtual void CreateDeviceResources() override;
      //virtual void CreateWindowSizeDependentResources() override;
      //virtual void Render() override;

   public:
      // IFrameworkView Methods
      virtual void Initialize(_In_ Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
      virtual void SetWindow(_In_ Windows::UI::Core::CoreWindow^ window);
      virtual void Load(_In_ String^ entryPoint);
      virtual void Run();
      virtual void Uninitialize();
      virtual Windows::Foundation::Rect get_window_rect();
      virtual Windows::Foundation::Point get_cursor_pos();
      

   private:
      // Event Handlers
      void OnWindowSizeChanged(
         _In_ Windows::UI::Core::CoreWindow^ sender,
         _In_ Windows::UI::Core::WindowSizeChangedEventArgs^ args
         );

      void DpiChanged(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj);

      void DisplayContentsInvalidated(::Windows::Graphics::Display::DisplayInformation ^ sender, Object ^ obj);

      void OnActivated(
         _In_ Windows::ApplicationModel::Core::CoreApplicationView^ applicationView,
         _In_ Windows::ApplicationModel::Activation::IActivatedEventArgs^ args
         );

      void OnSuspending(
         _In_ Object^ sender,
         _In_ Windows::ApplicationModel::SuspendingEventArgs^ args
         );

      void OnResuming(
         _In_ Object^ sender,
         _In_ Object^ args
         );

      void OnPointerMoved(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);

      void OnCharacterReceived(Windows::UI::Core::CoreWindow^, Windows::UI::Core::CharacterReceivedEventArgs^ args);
      void OnKeyDown(Windows::UI::Core::CoreWindow^, Windows::UI::Core::KeyEventArgs^ args);
      void OnKeyUp(Windows::UI::Core::CoreWindow^, Windows::UI::Core::KeyEventArgs^ args);
      void OnPointerPressed(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);
      void OnPointerReleased(Windows::UI::Core::CoreWindow^, Windows::UI::Core::PointerEventArgs^ args);


      //Microsoft::WRL::ComPtr<ID2D1SolidColorBrush>                    m_blackBrush;
      //Microsoft::WRL::ComPtr<IDWriteTextFormat>                       m_textFormat;
      //Microsoft::WRL::ComPtr<IDWriteTypography>                       m_textTypography;
      //Microsoft::WRL::ComPtr<IDWriteTextLayout>                       m_textLayout;
      //SampleOverlay^                                                  m_sampleOverlay;
      
   };


   ref class directx_application_source :
      Windows::ApplicationModel::Core::IFrameworkViewSource
   {
   internal:

      ::base::system * m_pbasesystem;

      string m_strId;

      directx_application_source(::base::system * paxissystem,const string & strId);

   public:

      virtual Windows::ApplicationModel::Core::IFrameworkView ^ CreateView();

   };


   CLASS_DECL_BASE directx_application_source ^ new_directx_application_source(::base::system * psystem, const string & str);


} // namespace metrowin



