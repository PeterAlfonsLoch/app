#pragma once


namespace windows
{


   class CLASS_DECL_AXIS message_queue:
      virtual public ::user::message_queue
   {
   public:


      HWND                             m_hwnd;

      //sp(::user::interaction)          m_spuiMessage;
      message_queue_listener *         m_plistener;


      message_queue(::aura::application * papp);
      virtual ~message_queue();


      virtual bool create_message_queue(const char * pszName,::user::message_queue_listener * plistener = NULL);

      virtual void message_handler(signal_details * pobj);

      virtual void message_queue_message_handler(signal_details * pobj);

      virtual bool message_queue_is_initialized();

      virtual bool message_queue_set_timer(uint_ptr uiId,DWORD dwMillis);

      virtual bool message_queue_post_message(uint32_t uiMessage,WPARAM wparam = 0,lparam lparam = 0);

      virtual LRESULT message_queue_send_message(uint32_t uiMessage,WPARAM wparam = 0,lparam lparam = 0);

      virtual bool message_queue_del_timer(uint_ptr uiId);

      virtual bool message_queue_destroy();

      virtual void * message_queue::message_queue_get_os_handle();

      static LRESULT CALLBACK WindowProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
      LRESULT window_proc(UINT message,WPARAM wparam,LPARAM lparam);

   };


} // namespace windows


