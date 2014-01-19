#pragma once


namespace async
{

   struct callback
   {
   };




   struct CLASS_DECL_BASE token
   {
      token *     m_ptoken;
      uint_ptr    m_uiToken;
      token()
      {
         m_ptoken = NULL;
         m_uiToken = 0;
      }
      token(const token & token)
      {
         m_ptoken = (struct token *) &token;
         m_uiToken = token.m_uiToken;
      }
      void set_token(uint_ptr uiTokenValue)
      {
         if(m_ptoken != NULL)
         {
            m_ptoken->set_token(uiTokenValue);
         }
         else
         {
            m_uiToken = uiTokenValue;
         }
      }

      uint_ptr get_token()
      {
         if(m_ptoken != NULL)
         {
            return m_ptoken->get_token();
         }
         else
         {
            return m_uiToken;
         }
      }
      token & operator = (const token & token)
      {
         m_ptoken = (struct token *) &token;
         m_uiToken = token.m_uiToken;
         return *this;
      }

      static token none()
      {
         token t;
         t.m_ptoken = (token *) -1;
         t.m_uiToken = (uint_ptr) -1;
         return t;
      }

      bool is_null()
      {
         return m_ptoken == (token *) -1;
      }

      bool is_set()
      {
         return !is_null();
      }

   };

   struct CLASS_DECL_BASE registration_token : public token
   {

   };


   struct CLASS_DECL_BASE cancellation_token : public token
   {
      callback *   m_pcallback;
      void(callback ::*m_pfnCancel)();

      cancellation_token()
      {
         m_pcallback = NULL;
         m_pfnCancel = NULL;
      }

      cancellation_token(const token & token)
      {
         m_ptoken = (struct token *) &token;
         m_uiToken = token.m_uiToken;
      }

      cancellation_token(const cancellation_token & token)
      {
         m_ptoken = (struct token *) &token;
         m_uiToken = token.m_uiToken;
         m_pcallback = token.m_pcallback;
         m_pfnCancel = token.m_pfnCancel;
      }

      void cancel()
      {
         set_token(1);
      }

      cancellation_token & operator = (const cancellation_token & token)
      {
         m_ptoken = (struct cancellation_token *) &token;
         m_uiToken = token.m_uiToken;
         m_pcallback = token.m_pcallback;
         m_pfnCancel = token.m_pfnCancel;
         return *this;
      }


      template < class T >
      registration_token register_callback(T * p, void(T::*pfnCancel)())
      {
         m_pcallback = (callback *) p;
         m_pfnCancel = (void(callback ::*)()) pfnCancel;
         registration_token t;
         t.m_ptoken = m_ptoken;
         t.m_uiToken = m_uiToken;
         return t;
      }

      void deregister_callback(registration_token t)
      {
         if(t.m_ptoken == this)
         {
            m_pcallback = NULL;
            m_pfnCancel = NULL;
         }
      }

   };


   enum e_status
   {

      status_error,
      status_run,
      status_cancel,
      status_complete

   };


   template < class T >
   class task_completion_event;


   template < class T >
   class CLASS_DECL_BASE task :
      public thread_layer
   {
   public:


      class completion_callback;


      typedef void (completion_callback :: *LPFN_COMPLETION_CALLBACK)(task < T > & task, e_status estatus);


      T *                           m_presult;
      completion_callback *         m_pcompletioncallback;
      LPFN_COMPLETION_CALLBACK      m_pfncompletioncallback;
      e_status                      m_estatus;
      task_completion_event < T > * m_pev;
      cancellation_token            m_cancellationtoken;



      inline task(task_completion_event < T > & ev, cancellation_token token)
      {

         m_presult                  = NULL;
         m_pcompletioncallback      = NULL;
         m_pfncompletioncallback    = NULL;
         m_estatus                  = status_complete;
         m_pev                      = &ev;
         m_cancellationtoken        = token;
      }

      virtual ~task()
      {

         close();

      }


      template < class COMPLETION_CALLBACK >
      void set_completion_callback(COMPLETION_CALLBACK * pobject, void (COMPLETION_CALLBACK :: *pfncompletioncallback)(task < T > & task, e_status estatus))
      {

         m_pcompletioncallback      = static_cast < completion_callback * > (pobject);

         m_pfncompletioncallback    = static_cast < completion_callback * > (pfncompletioncallback);

      }



      virtual void cancel()
      {

         defer_call_completion(status_cancel);

      }

      void defer_call_completion(e_status estatus)
      {

         m_estatus = estatus;

         if(m_pcompletioncallback == NULL)
            return;

         if(m_pfncompletioncallback == NULL)
            return;

         (m_pcompletioncallback->*m_pfncompletioncallback)(*this, m_estatus);

      }

      virtual int32_t run()
      {

         defer_call_completion(status_complete);

         return 0;

      }

      virtual T * wait(uint32_t dwMillis = INFINITE)
      {

         ::thread_layer::wait_thread(dwMillis);

         return m_presult;

      }

      virtual void close()
      {

         if(m_presult != NULL)
         {

            destroy_result();

            m_presult = NULL;

         }

      }

      virtual void destroy_result()
      {

         if(m_presult == NULL)
            return;

         delete m_presult;

      }

   };



   inline void cancel_current_task()
   {
      throw "cancel_current_task";
   }

   template < typename T >
   class task_completion_event
   {
   public:
      event m_event;
      bool set(T r )
      {
         m_event.set_event();
         return true;
      }
   };

   template < >
   class task_completion_event < void >
   {
   public:
      event m_event;
      bool set()
      {
         m_event.set_event();
         return true;
      }
   };

   template < class T >
   inline task < T > * create_task(task_completion_event < T > & ev, cancellation_token token = token::none())
   {
      return new task < T > (ev, token);
   }

} // namespace async



template < typename T >
class waiter_for_async_task
{
public:

   T *                                                m_presult;
   async::task < T > *                                m_ptask;


   waiter_for_async_task(::async::task < T > * ptask)
   {

      m_ptask = ptask;

   }


   virtual ~waiter_for_async_task()
   {

   }


   T * wait(uint32_t dwMillis = INFINITE)
   {

      m_presult = m_ptask->wait(dwMillis);

      return m_presult;

   }

};




template < typename T >
inline  T * wait(::async::task < T > * ptask, uint32_t dwMillis = INFINITE)
{

   return waiter_for_async_task < T > (ptask).wait(dwMillis);

}


