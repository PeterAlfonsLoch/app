#pragma once


namespace metrowin
{


   ref class directx_application : 
      public Windows::ApplicationModel::Core::IFrameworkView,
      public ::aura::system_window
   {
   internal:


      Windows::Foundation::Point m_ptLastCursor;

      Platform::String ^ m_strId;

      Platform::Agile<Windows::UI::Core::CoreWindow>  m_window;

            directx_base ^                         m_directx;
            bool  m_bFontopusShift;

      mutex m_mutex;

      ::aura::system * m_psystem;
      ::aura::application * m_papp;

      bool        m_bLeftButton;
      bool        m_bMiddleButton;
      bool        m_bRightButton;

      Windows::Foundation::Rect m_rectLastWindowRect;

      ::aura::application * get_app() const
      {
         return m_papp;
      }


      directx_application(::aura::system * psystem, Platform::String ^ strId);


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
      virtual void Load(_In_ Platform::String^ entryPoint);
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

      void DpiChanged(::Windows::Graphics::Display::DisplayInformation ^ sender, Platform::Object ^ obj);

      void DisplayContentsInvalidated(::Windows::Graphics::Display::DisplayInformation ^ sender, Platform::Object ^ obj);

      void OnActivated(
         _In_ Windows::ApplicationModel::Core::CoreApplicationView^ applicationView,
         _In_ Windows::ApplicationModel::Activation::IActivatedEventArgs^ args
         );

      void OnSuspending(
         _In_ Platform::Object^ sender,
         _In_ Windows::ApplicationModel::SuspendingEventArgs^ args
         );

      void OnResuming(
         _In_ Platform::Object^ sender,
         _In_ Platform::Object^ args
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

      Platform::String ^ m_strId;

      directx_application_source(Platform::String ^ strId);

   public:

      virtual Windows::ApplicationModel::Core::IFrameworkView ^ CreateView();

   };


   CLASS_DECL_AURA directx_application_source ^ new_directx_application_source(Platform::String ^ id);


} // namespace metrowin



