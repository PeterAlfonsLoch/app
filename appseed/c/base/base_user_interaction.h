#pragma once


namespace user
{


   class interaction;


    class CLASS_DECL_c interaction_base :
        virtual public root
   {
   public:


      ::thread_base *         m_pthread;
      ::user::interaction *   m_pui;


      virtual LRESULT message_handler(LPMESSAGE lpmessage) = 0;
      virtual sp(interaction_base) get_parent_base() const = 0;
      virtual sp(interaction_base) set_parent_base(sp(interaction_base) pguieParent) = 0;
      virtual oswindow get_parent_handle() const = 0;
      virtual bool is_message_only_window() const = 0;
#ifdef METROWIN
      virtual Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window() = 0;
#endif

   };


} // namespace user




