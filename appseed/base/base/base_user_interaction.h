#pragma once


namespace user
{


   class interaction;


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
#ifdef METROWIN
      virtual Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window() = 0;
#endif

   };


} // namespace user




