//
//  multithreading_thread_impl.h
//  base
//
//  Created by Carlos Gustavo Cecyn Lundgren on 16/05/14.
//
//
#pragma once


class thread_startup
{
public:


   ::thread *              m_pthread;
   ::thread_impl *         m_pthreadimpl;
   manual_reset_event      m_event;
   manual_reset_event      m_event2;
   DWORD                   m_dwCreateFlags;
   bool                    m_bError;


   thread_startup(sp(::base::application) papp);
   ~thread_startup();





};


class CLASS_DECL_BASE thread_impl :
virtual public thread
{
public:


   HTHREAD     m_hthread;
   uint32_t    m_uiThread;


   virtual bool pre_init_instance();
   
   virtual bool initialize_instance();

   virtual void pre_translate_message(signal_details * pobj);
   
   virtual void process_window_procedure_exception(::exception::base*,signal_details * pobj);

   virtual void process_message_filter(int32_t code,signal_details * pobj);


   virtual int32_t thread_entry(::thread_startup * pstartup);
   virtual int32_t main();
   virtual int32_t thread_term(int32_t nResult);


   virtual bool create_thread(int32_t epriority,uint32_t dwCreateFlagsParam,uint_ptr nStackSize,LPSECURITY_ATTRIBUTES lpSecurityAttrs);


};




