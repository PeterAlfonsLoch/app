#pragma once


// Note: afxData.cxBorder and afxData.cyBorder aren't used anymore
#define CX_BORDER   1
#define CY_BORDER   1



namespace user
{


   class interaction;

   class base_interaction;


    class CLASS_DECL_c base_interaction :
        virtual public root
   {
   public:


      ::base_thread *         m_pthread;
      ::user::interaction *   m_pui;


      virtual LRESULT message_handler(LPMESSAGE lpmessage) = 0;
      virtual sp(base_interaction) get_parent_base() const = 0;
      virtual sp(base_interaction) set_parent_base(sp(base_interaction) pguieParent) = 0;
      virtual oswindow get_parent_handle() const = 0;
      virtual bool is_message_only_window() const = 0;
#if defined(METROWIN) && defined(__cplusplus_winrt)
      static Platform::Agile<Windows::UI::Core::CoreWindow> (* s_get_os_window)(base_interaction * pui);
      Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window()
      {
         return get_os_window(this);
      }
      static Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window(base_interaction * pui)
      {
         return (*s_get_os_window)(pui);
      }
      static Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window_default(base_interaction * pui)
      {
         UNREFERENCED_PARAMETER(pui);
         return nullptr;
      }
#endif

   };


} // namespace user




