#pragma once


namespace async
{


   enum e_status
   {
      status_error,
      status_run,
      status_cancel,
      status_complete,
   };


   template < class T >
   class CLASS_DECL_c task :
      public thread_layer
   {
   public:


      class completion_callback;


      typedef void (completion_callback :: *LPFN_COMPLETION_CALLBACK)(task < T > & task, e_status estatus);


      T *                        m_presult;                         
      completion_callback *      m_pcompletioncallback;
      LPFN_COMPLETION_CALLBACK   m_pfncompletioncallback;
      e_status                   m_estatus;


      task()
      {

         m_presult                  = NULL;
         m_pcompletioncallback      = NULL;
         m_pfncompletioncallback    = NULL;
         m_estatus                  = status_complete;

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



      virtual bool cancel()
      {

         defer_call_completion(status_cancel);

      }

      void defer_call_completion()
      {

         if(m_pcompletioncallback == NULL)
            return;

         if(m_pfncompletioncallback == NULL)
            return;

         (m_pcompletioncallback->*m_pfncompletioncallback)(*this, m_estatus); 

         return true;

      }

      virtual int run()
      { 
      
         defer_call_completion(); 
         
         return 0;
      
      }

      virtual T * wait()
      { 
         
         ::thread_layer::wait_thread();

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


} // namespace async



