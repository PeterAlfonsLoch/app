#include "framework.h"





bool thread::s_bAllocReady = false;


thread::thread()
{

   CommonConstruct();

}




thread::thread(sp(::base::application) papp) :
element(papp),
m_set(papp)
{

   CommonConstruct();

   if (papp == NULL)
      return;
   set_app(papp);
   if (!s_bAllocReady)
      return;
   m_pthreadimpl.create(allocer());
   m_pthreadimpl->m_pthread = this;
   m_pthreadimpl->construct();

   if(m_pbaseapp != NULL && m_pbaseapp->m_pbasesession != NULL)
   {

      m_bZipIsDir = m_pbaseapp->m_pbasesession->m_bZipIsDir;

   }

}


thread::thread(sp(::base::application) papp, __THREADPROC pfnThreadProc, LPVOID pParam) :
element(papp)
{

   CommonConstruct();

   m_pthreadimpl.create(allocer());
   m_pthreadimpl->m_pthread = this;
   m_pthreadimpl->construct(pfnThreadProc, pParam);

   if(m_pbaseapp != NULL && m_pbaseapp->m_pbasesession != NULL)
   {

      m_bZipIsDir = m_pbaseapp->m_pbasesession->m_bZipIsDir;

   }

}


void thread::CommonConstruct()
{

   m_dwAlive = ::get_tick_count();

   m_pmutex = new mutex();

   m_bReady = false;
   m_bRun = true;
   m_pappDelete = NULL;
   m_pbReady = NULL;

   m_puiActive = NULL;
   m_puiMain = NULL;

   m_iReturnCode = 0;

   m_bZipIsDir = true;

   m_pslUser = NULL;

}



thread::~thread()
{

   if(m_pmutex != NULL)
      delete m_pmutex;

}








void * thread::get_os_data() const
{
   return m_pthreadimpl == NULL ? NULL : m_pthreadimpl->get_os_data();
}


int_ptr thread::get_os_int() const
{

   return m_pthreadimpl == NULL ? -1 : m_pthreadimpl->get_os_int();

}


HTHREAD thread::get_os_handle() const
{

   return (HTHREAD)get_os_data();

}




void thread::start()
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->start();

}


bool thread::verb()
{

   return true;

}


bool thread::begin(int32_t epriority, uint_ptr nStackSize, uint32_t dwCreateFlags, LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if (m_pthreadimpl.is_null())
      return false;

   m_pthreadimpl->m_pthread = this;

   return m_pthreadimpl->begin(epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);

}


bool thread::create_thread(int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if (m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->create_thread(epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);

}


bool thread::begin_synch(int32_t * piStartupError, int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if(m_pthreadimpl.is_null())
      return false;

   m_pthreadimpl->m_pthread = this;

   return m_pthreadimpl->begin_synch(piStartupError, epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);

}


bool thread::create_thread_synch(int32_t * piStartupError,int32_t epriority,uint_ptr nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->create_thread_synch(piStartupError,epriority,nStackSize,dwCreateFlags,lpSecurityAttrs);

}


bool thread::finalize()
{

   signal_close_dependant_threads();

   unregister_dependencies();

   wait_dependant_threads(minutes(1));

   if(m_pthreadimpl == NULL)
      return true;

   m_pthreadimpl->finalize();

   return true;

}


int32_t thread::exit()
{

   try
   {

      if (!finalize())
      {

         TRACE("There occurred errors durring application::finalize virtual member function");

      }

   }
   catch (...)
   {

   }

   return exit_instance();

}



int32_t thread::get_thread_priority()
{

   if(m_pthreadimpl.is_null())
      return -1;

   return m_pthreadimpl->get_thread_priority();

}


bool thread::set_thread_priority(int32_t epriority)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->set_thread_priority(epriority);

}


uint32_t thread::ResumeThread()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->ResumeThread();

}


bool thread::post_thread_message(UINT message, WPARAM wParam, lparam lParam)
{

   if (m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->post_thread_message(message, wParam, lParam);

}


void thread::set_os_data(void * pvoidOsData)
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->set_os_data(pvoidOsData);

}


void thread::set_os_int(int_ptr iData)
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->set_os_int(iData);

}


void thread::on_keep_alive()
{

   m_dwAlive = ::get_tick_count();

}


bool thread::is_alive()
{

   if(m_pthreadimpl.is_null())
      return false;

   if (!m_bRun)
      return false;

   //if ((::get_tick_count() - m_dwAlive) > ((5000) * 91))
     // return false;

   return true;

}

bool thread::has_message()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->has_message();


}


bool thread::is_auto_delete()
{

   return m_bAutoDelete;

}


wait_result thread::wait(const duration & duration)
{

   if(m_pthreadimpl.is_null())
      return wait_result();

   return m_pthreadimpl->wait(duration);

}


void thread::set_priority(int32_t priority)
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->set_priority(priority);

}

int32_t thread::priority()
{

   if(m_pthreadimpl.is_null())
      return 0x80000000;

   return m_pthreadimpl->priority();

}



CLASS_DECL_BASE void thread_alloc_ready(bool bReady)
{

   thread::s_bAllocReady = bReady;

}


void thread::process_message_filter(int32_t code, signal_details * pobj)
{

   if(m_pthreadimpl.is_null())
      return;

   return  m_pthreadimpl->process_message_filter(code, pobj);

}


bool thread::post_message(sp(::user::interaction) pui, UINT message, WPARAM wParam, lparam lParam)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->post_message(pui, message, wParam, lParam);

}

bool thread::pre_init_instance()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->pre_init_instance();

}

bool thread::on_run_exception(::exception::exception & e)
{

   try
   {

      if (m_pthreadimpl.is_null())
         return false;

      return m_pthreadimpl->on_run_exception(e);

   }
   catch (::exception::standard_access_violation &)
   {

      return false;

   }
   catch (::exception::exception & e)
   {

      throw e;

   }
   catch (...)
   {

      return false;

   }

}

bool thread::initialize_instance()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->initialize_instance();

}


message::e_prototype thread::GetMessagePrototype(UINT uiMessage, UINT uiCode)
{

   if(m_pthreadimpl.is_null())
      return ::message::PrototypeNone;

   return m_pthreadimpl->GetMessagePrototype(uiMessage, uiCode);

}

bool thread::pre_run()
{

   register_dependencies();

   return true;

}

int32_t thread::run()
{

   if(m_pthreadimpl.is_null())
      return -1;

   return m_pthreadimpl->run();

}


void thread::pre_translate_message(signal_details * pobj)
{

   if (m_pthreadimpl.is_null())
      return;

   return m_pthreadimpl->pre_translate_message(pobj);

}


bool thread::pump_message()
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->pump_message();

}


bool thread::on_idle(LONG lCount)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->on_idle(lCount);

}


bool thread::is_idle_message(signal_details * pobj)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->is_idle_message(pobj);

}


bool thread::is_idle_message(LPMESSAGE lpmsg)
{

   if(m_pthreadimpl.is_null())
      return false;

   return m_pthreadimpl->is_idle_message(lpmsg);

}


int32_t thread::exit_instance()
{

   if (m_pthreadimpl.is_null())
      return 0;

   return m_pthreadimpl->exit_instance();

}


void thread::process_window_procedure_exception(::exception::base* e, signal_details * pobj)
{

   if(m_pthreadimpl.is_null())
      return;

   return m_pthreadimpl->process_window_procedure_exception(e,pobj);

}



void thread::add(sp(::user::interaction) pui)
{

   if (m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->add(pui);

}


void thread::remove(::user::interaction * pui)
{

   if (m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->remove(pui);

}


::count thread::get_ui_count()
{

   if (m_pthreadimpl.is_null())
      return 0;

   return m_pthreadimpl->get_ui_count();

}


::user::interaction * thread::get_ui(index iIndex)
{

   if (m_pthreadimpl.is_null())
      return NULL;

   return m_pthreadimpl->get_ui(iIndex);

}


void thread::set_timer(sp(::user::interaction) pui, uint_ptr nIDEvent, UINT nEllapse)
{

   if (m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->set_timer(pui, nIDEvent, nEllapse);

}


void thread::unset_timer(sp(::user::interaction) pui, uint_ptr nIDEvent)
{

   if (m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->unset_timer(pui, nIDEvent);

}


void thread::set_auto_delete(bool bAutoDelete)
{

   m_bAutoDelete = bAutoDelete;

}


void thread::set_run(bool bRun)
{

   m_bRun = bRun;

}


event & thread::get_finish_event()
{

   if (m_pthreadimpl.is_null())
      return *((event *)NULL);

   return m_pthreadimpl->get_finish_event();

}


bool thread::get_run()
{

   return m_bRun;

}




sp(::user::interaction) thread::get_active_ui()
{

   return m_puiActive;

}


sp(::user::interaction) thread::set_active_ui(sp(::user::interaction) pui)
{

   return m_puiActive = pui;

}


void thread::step_timer()
{

   if (m_pthreadimpl.is_null())
      return;

   return m_pthreadimpl->step_timer();

}


bool thread::on_run_step()
{

   if (m_pthreadimpl.is_null())
      return false;


   step_timer();

   sp(::base::application) papp = (this);

   m_dwAlive = ::get_tick_count();

   if (papp != NULL)
   {

      papp->m_dwAlive = m_dwAlive;

   }

   sp(::base::application) pappP = (this);

   if (pappP != NULL)
   {

      pappP->m_dwAlive = m_dwAlive;

   }

   try
   {

      if (!verb())
         return false;

   }
   catch (::exit_exception & e)
   {

      throw e;

   }
   catch (::exception::exception & e)
   {

      if (!Application.on_run_exception(e))
         throw exit_exception(get_app());

   }
   catch (...)
   {

   }

   return true;

}


int32_t thread::main()
{

   return m_pthreadimpl->main();

}



void thread::assert_valid() const
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->assert_valid();

}


void thread::dump(dump_context & dumpcontext) const
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->dump(dumpcontext);

}


void thread::Delete()
{


   release();

}


void thread::dispatch_thread_message(signal_details * pobj)  // helper
{
   m_pthreadimpl->dispatch_thread_message(pobj);

}

void thread::wait()
{

   if(m_pthreadimpl.is_null())
      return;

   return m_pthreadimpl->wait();

}


int_ptr thread::item() const
{

   if(m_pthreadimpl.is_null())
      return -1;

   return m_pthreadimpl->item();

}


int thread::get_x_window_count() const
{

   if (m_pthreadimpl.is_null())
      return 0;

   return m_pthreadimpl->get_x_window_count();

}




void thread::post_to_all_threads(UINT message,WPARAM wparam,LPARAM lparam)
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->post_to_all_threads(message,wparam,lparam);

}


void thread::register_dependant_thread(::thread * pthread)
{

   if(pthread == this)
      return;

   {

      synch_lock sl(m_pmutex);

      m_threadptraDependant.add_unique(pthread);

   }

   {

      synch_lock slThread(pthread->m_pmutex);

      pthread->m_threadptraDependency.add_unique(this);

   }

}


void thread::unregister_dependant_thread(::thread * pthread)
{

   {

      synch_lock sl(m_pmutex);

      m_threadptraDependant.remove(pthread);

   }

   {

      synch_lock slThread(pthread->m_pmutex);

      pthread->m_threadptraDependency.remove(this);

   }

}


void thread::signal_close_dependant_threads()
{

   synch_lock sl(m_pmutex);

   for(index i = m_threadptraDependant.get_upper_bound(); i >= 0;)
   {

      try
      {

         synch_lock slThread(m_threadptraDependant[i]->m_pmutex);

         m_threadptraDependant[i]->m_bRun = false;

         i--;

      }
      catch(...)
      {

      }

      sl.unlock();

      sl.lock();


   }

}


void thread::wait_dependant_threads(duration & duration)
{

   DWORD dwStart = ::get_tick_count();

   while(::get_tick_count() - dwStart < duration.get_total_milliseconds())
   {

      {

         synch_lock sl(m_pmutex);

         if(m_threadptraDependant.get_count() <= 0)
            break;

         for(index i = 0; i < m_threadptraDependant.get_count(); i++)
         {
            TRACE(string("---"));
            TRACE(string("DEPENDENCY : ") + typeid(*this).raw_name() + string(" (") + ::str::from(this) + ")");
            TRACE(string("dependant  :") + typeid(*m_threadptraDependant[i]).raw_name() + string(" (") + ::str::from(m_threadptraDependant[i]) + ")");

         }

      }

      Sleep(11);

   }

}

void thread::register_dependencies()
{

   // register default dependencies

   sp(::base::application) papp = this;

   sp(::base::session) psession = this;

   sp(::base::system) psystem = this;

   if(&Application != NULL)
   {

      Application.register_dependant_thread(this);

      if(psystem == NULL && &session() != NULL)
      {

         session().register_dependant_thread(this);

         if(session().m_pplatformcomposite != NULL)
         {

            session().m_pplatformcomposite->register_dependant_thread(this);

         }

      }

      if(&System != NULL)
      {

         System.register_dependant_thread(this);

      }

   }

}



void thread::unregister_dependencies()
{

   synch_lock sl(m_pmutex);

   for(index i = m_threadptraDependency.get_upper_bound(); i >= 0;)
   {

      try
      {

         synch_lock slThread(m_threadptraDependency[i]->m_pmutex);

         m_threadptraDependency[i]->unregister_dependant_thread(this);

         i--;

      }
      catch(...)
      {

      }

      sl.unlock();

      sl.lock();

   }

}


void thread::do_events()
{

   if(m_pthreadimpl.is_null())
      return;

   m_pthreadimpl->do_events();

}


void thread::do_events(const duration & duration)
{

   DWORD dwEnd = (DWORD) (::get_tick_count() + duration.get_total_milliseconds());

   do
   {
    
      do_events();

   } while(::get_tick_count() < dwEnd);

}
