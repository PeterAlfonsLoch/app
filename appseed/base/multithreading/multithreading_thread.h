#pragma once


#pragma once




#ifdef WINDOWSEX

typedef HANDLE HTHREAD;

#else

typedef hthread * HTHREAD;

#endif


#pragma once




/*namespace win
{
class CLASS_DECL_BASE message
{
public:
sp(::user::interaction)  m_pui;
UINT              m_uiMessage;
WPARAM            m_wparam;
LPARAM            m_lparam;
LRESULT send();
static UINT ThreadProcSendMessage(LPVOID lp);
static void post(sp(::user::interaction) puie, UINT uiMessage, WPARAM wparam, LPARAM lparam, int32_t nPriority = 0);
};

} // namespace win*/

/**
* \file		src/lib/pal/windows/thread_windows.hpp
* \brief	Platform independent threads and synchronization objects (windows version)
*/
/**
* \file		src/lib/pal/linux/thread_linux.hpp
* \brief	Platform independent threads and synchronization objects (linux version)
*/

//#ifndef GEN_PAL_THREAD_WINDOWS_HPP
//#define GEN_PAL_THREAD_WINDOWS_HPP

// xxx #include "../waitable.hpp"

//#include <process.h>

//#include <stdexcept>
//#include <limits>


class event;


class thread;


#ifdef WINDOWS

///  \brief		global function to wait on a waitable item for a specified time
///  \param		waitableItem item to wait for (can be event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
inline wait_result wait(event_base & waitableItem, const duration & duration = duration::infinite())
{
   return waitableItem.wait(duration);
}

///  \brief		global function to wait on a waitable item for a specified time
///  \param		waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
wait_result wait(size_t numberOfItems, event_base * waitableItems[], const duration & duration = duration::infinite(), bool waitForAll = false);

#else

///  \brief		global function to wait on a waitable item for a specified time
///  \param		waitableItem item to wait for (can be event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
wait_result wait(event_base & waitableItem, const duration & duration = duration::infinite());

///  \brief		global function to wait on a waitable item for a specified time
///  \param		waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
///  \param		duration time period to wait for item (default: infinite)
///  \return	result of waiting action as defined in wait_result
wait_result wait(size_t numberOfItems, event_base * waitableItems[], const duration& duration = duration::infinite(), bool waitForAll = false);

#endif

class CLASS_DECL_BASE heap_item
{
public:


   byte *      m_pbStart;
   byte *      m_pbEnd;
#ifdef METROWIN
   DWORD64     m_dwTickCount;
#else
   uint32_t       m_dwTickCount;
#endif


   inline heap_item()
   {
      m_pbStart = NULL;
      m_pbEnd = NULL;
   }


#ifdef METROWIN
   inline heap_item(void * p, ::primitive::memory_size iSize, DWORD64 dwTick)
#else
   inline heap_item(void * p, ::primitive::memory_size iSize, uint32_t dwTick)
#endif
   {
      m_pbStart = (byte *)p;
      m_pbEnd = ((byte *)p) + max(iSize - 1, 0);
      m_dwTickCount = dwTick;
   }


   inline char compare(void * p)
   {
      if (((byte *)p) <= m_pbStart)
         return 1;
      else if (((byte *)p) >= m_pbEnd)
         return -1;
      else
         return 0;
   }

   inline bool contains(void * p)
   {
      if (((byte *)p) <= m_pbStart)
         return false;
      else if (((byte *)p) >= m_pbEnd)
         return false;
      else
         return true;
   }

};

class CLASS_DECL_BASE heap_item_array :
   public array < heap_item, heap_item >
{
public:

#ifdef METROWIN
   DWORD64 m_dwLastCleanup;
#else
   uint32_t m_dwLastCleanup;
#endif

   inline void add_item(void * p, ::primitive::memory_size iSize)
   {
#ifdef METROWIN
      add(heap_item(p, iSize, GetTickCount64()));
      if (GetTickCount64() > m_dwLastCleanup + 10000)
#else
      add(heap_item(p, iSize, get_tick_count()));
      if (get_tick_count() > m_dwLastCleanup + 10000)
#endif
      {
         cleanup();
      }
   }

   inline void cleanup()
   {
#ifdef METROWIN
      DWORD64 dwLimit = GetTickCount64() - 1000;
#else
      DWORD64 dwLimit = get_tick_count() - 1000;
#endif
      for (int32_t i = 0; i < this->get_count();)
      {
         if (dwLimit > m_pData[i].m_dwTickCount)
         {
            remove_at(i);
         }
         else
         {
            i++;
         }
      }
#ifdef METROWIN
      m_dwLastCleanup = GetTickCount64();
#else
      m_dwLastCleanup = get_tick_count();
#endif
   }

   inline bool find(void * p, bool bRemove)
   {
      UNREFERENCED_PARAMETER(bRemove);

      for (int32_t mi = 0; mi < this->get_count(); mi++)
      {
         if (m_pData[mi].contains(p))
         {
            remove_at(mi);
            return true;
         }
      }
      return false;
   }

   /*inline void set_heap_alloc(sp(element) pca)
   {
   if(find(pca, true))
   {
   pca->m_ulFlags |= element::flag_heap_alloc;
   }
   }*/

};




class thread;


typedef smart_pointer < thread > thread_sp;


class CLASS_DECL_BASE thread :
   virtual public command_target,
#ifdef WINDOWS
   virtual public ::exception::translator,
#endif
   virtual public spa(::user::interaction),
   virtual public ::core::live_object,
   virtual public event_base
{
public:
   /// thread ID, used to ensure that the thread that calls one of the
   /// wait methods is really the thread represented by the Thread class
   //	uint32_t threadId_;


   //	private:

   static bool                            s_bAllocReady;
   mutex                                  m_mutex;
   bool                                   m_bRun;

   thread_sp                              m_p;
   sp(::user::interaction_ptr_array)      m_puiptra;
   sp(::user::interaction::timer_array)   m_ptimera;
   bool                                   m_bAutoDelete;       // enables 'delete this' after thread termination
   uint_ptr                               m_dwAlive;
   bool                                   m_bReady;
   int32_t                                m_iReturnCode;
   sp(::base::application)                   m_pappDelete;
   sp(::user::interaction)                m_puiMain;           // main window (usually same System.GetMainWnd())
   sp(::user::interaction)                m_puiActive;         // active main window (may not be GetMainWnd())
   bool *                                 m_pbReady;
   property_set                           m_set;
   string                                 m_strWorkUrl;


   thread();
   thread(sp(::base::application) papp);
   thread(sp(::base::application) papp, __THREADPROC pfnThreadProc, LPVOID pParam);
   virtual ~thread();

   ///  \brief		starts thread on first call
   virtual void start();

   virtual void * get_os_data() const;
   virtual int_ptr get_os_int() const;


   virtual HTHREAD get_os_handle() const;


   virtual void set_p(thread * p);


   virtual void set_os_data(void * pvoidOsData);
   virtual void set_os_int(int_ptr iData);


   friend bool __internal_pre_translate_message(MESSAGE * pMsg);

   virtual void construct();
   virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);

   //      virtual int32_t main();

   virtual void CommonConstruct();

   //      virtual bool begin(int32_t epriority = scheduling_priority_normal, uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

   //      virtual bool create_thread(int32_t epriority = ::get_scheduling_priority_normal(), uint32_t dwCreateFlags = 0, uint_ptr nStackSize = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

   //      virtual int32_t get_thread_priority();
   //    virtual bool set_thread_priority(int32_t epriority);

   //virtual uint32_t SuspendThread();
   //      virtual uint32_t ResumeThread();
   //    virtual bool post_thread_message(UINT message, WPARAM wParam, LPARAM lParam);
   //  virtual bool post_message(sp(::user::interaction) pui, UINT message, WPARAM wParam, LPARAM lParam);

   //      virtual bool PreInitInstance();

   // called when occurs an standard_exception exception in run
   // return true to call run again
   //    virtual bool on_run_exception(::exception::exception &);

   // Overridables
   // thread initialization
   //  virtual bool initialize_instance();

   virtual bool finalize();

   virtual int32_t exit();

   //virtual message::e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode);

   // running and idle processing
   //      virtual int32_t run();
   //      virtual void pre_translate_message(signal_details * pobj);
   //      virtual bool pump_message();     // low level message pump
   //      virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
   //      virtual bool is_idle_message(signal_details * pobj);  // checks for special messages

   // thread termination
   //      virtual int32_t exit_instance(); // default will 'delete this'

   // Advanced: exception handling
   //      virtual void ProcessWndProcException(::exception::base * e, signal_details * pobj);

   // Advanced: handling messages sent to message filter hook
   //      virtual void ProcessMessageFilter(int32_t code, signal_details * pobj);

   // Advanced: virtual access to GetMainWnd()
   //      virtual sp(::user::interaction) GetMainWnd();
   //      virtual sp(::user::interaction) SetMainWnd(sp(::user::interaction) pui);

   //using spa(::user::interaction)::add;
   //      virtual void add(sp(::user::interaction) pui);

   //using spa(::user::interaction)::remove;
   //      virtual void remove(sp(::user::interaction) pui);

   //      virtual ::count get_ui_count();
   //      virtual ::user::interaction * get_ui(index iIndex);
   //      virtual void set_timer(sp(::user::interaction) pui, uint_ptr nIDEvent, UINT nEllapse);
   //      virtual void unset_timer(sp(::user::interaction) pui, uint_ptr nIDEvent);
   ////      virtual void set_auto_delete(bool bAutoDelete = true);
   ////      virtual void set_run(bool bRun = true);
   //      virtual event & get_finish_event();
   //      virtual bool get_run();
   //      virtual thread * get_app_thread();
   //      virtual sp(::user::interaction) get_active_ui();
   //      virtual sp(::user::interaction) set_active_ui(sp(::user::interaction) pui);
   //      virtual void step_timer();




   //      virtual void assert_valid() const;
   //    virtual void dump(dump_context & dumpcontext) const;

   //      virtual void Delete();
   // 'delete this' only if m_bAutoDelete == TRUE

   //      virtual void DispatchThreadMessageEx(signal_details * pobj);  // helper

   virtual void on_keep_alive();
   virtual bool is_alive();


   virtual bool has_message();

   virtual int get_x_window_count() const;


   /// This class represents a thread which can be put into a WaitableCollection also.
   //	class Thread : public WaitableItem
   //{
   //public:
   ///  \brief		default constructor
   //		Thread ();

   ///  \brief		waits on a waitable item for a specified time in this thread
   ///  \param		waitableItem item to wait for (can be event, socket, file, semaphore, ...)
   ///  \param		duration time period to wait for item (default: infinite)
   ///  \return	result of waiting action as defined in wait_result
   //wait_result wait(WaitableItem & waitableItem, const boost::posix_time::time_duration& duration=InfiniteTime);

   ///  \brief		waits on multiple waitable items for a specified time in this thread
   ///  \param		numberOfItems number of items to wait for
   ///  \param		waitableItems items to wait for (can be events, sockets, files, semaphores, ...)
   ///  \param		duration time period to wait for item (default: infinite)
   ///  \return	result of waiting action as defined in wait_result
   //wait_result wait(size_t numberOfItems, WaitableItem * waitableItems[], const boost::posix_time::time_duration& duration=InfiniteTime, bool waitForAll = false);
   // int32_t wait (uint32_t TimeoutMs, uint32_t NumberOfEvents, ...);

   //void suspend ()
   //{ ::SuspendThread(item()); }
   //
   //void resume ()
   //{ ::ResumeThread(item()); }

   ///  \brief		waits for signaling the thread forever
   //		virtual void wait();

   ///  \brief		waits for signaling the thread for a specified time
   ///  \param		duration time period to wait for thread
   ///  \return	result of waiting action as defined in wait_result
   virtual wait_result wait(const duration & duration);

   ///  \brief		sets thread priority
   ///  \param		new priority
   void set_priority(int32_t priority);

   ///  \brief		gets thread priority
   ///  \param		priority
   int32_t priority();

   ///  \brief		destructor
   //		virtual ~Thread()
   //	{}
   //
   //	Thread (const Thread &);				// no copy constructor
   //Thread & operator= (const Thread &);	// no assignment operator

   /*static uint32_t __stdcall startExecution_ (thread * thisThread)
   {
   thisThread->threadId_ = ::GetCurrentThreadId();
   uint32_t result = (*thisThread)();
   if (result == autodelete)
   delete thisThread;
   return result;
   }*/

   //virtual uint32_t operator() () = 0;

   virtual bool is_auto_delete();
   //};


   //#endif // #define GEN_PAL_THREAD_WINDOWS_HPP






   virtual bool begin(int32_t epriority = ::get_scheduling_priority_normal(), uint_ptr nStackSize = 0, uint32_t dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

   virtual bool create_thread(int32_t epriority = ::get_scheduling_priority_normal(), uint32_t dwCreateFlags = 0, uint_ptr nStackSize = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

   virtual int32_t get_thread_priority();
   virtual bool set_thread_priority(int32_t epriority);

   //      virtual uint32_t SuspendThread();
   virtual uint32_t ResumeThread();
   virtual bool post_thread_message(UINT message, WPARAM wParam = 0, lparam lParam = 0);
   virtual bool post_message(sp(::user::interaction) pui, UINT message, WPARAM wParam = 0, lparam lParam = 0);

   virtual bool PreInitInstance();

   // called when occurs an standard_exception exception in run
   // return true to call run again
   virtual bool on_run_exception(::exception::exception &);

   // Overridables
   // thread initialization
   virtual bool initialize_instance();

   virtual message::e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode);

   // running and idle processing
   virtual int32_t run();
   virtual void pre_translate_message(signal_details * pobj);
   virtual bool pump_message();     // low level message pump
   virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
   virtual bool is_idle_message(signal_details * pobj);  // checks for special messages

   // thread termination
   virtual int32_t exit_instance(); // default will 'delete this'

   // Advanced: exception handling
   virtual void ProcessWndProcException(::exception::base* e, signal_details * pobj);

   // Advanced: handling messages sent to message filter hook
   virtual void ProcessMessageFilter(int32_t code, signal_details * pobj);

   // Advanced: virtual access to GetMainWnd()
   virtual sp(::user::interaction) GetMainWnd();

   virtual sp(::user::interaction) SetMainWnd(sp(::user::interaction) pui);

   virtual void add(sp(::user::interaction) pui);
   virtual void remove(::user::interaction * pui);
   virtual ::count get_ui_count();
   virtual ::user::interaction * get_ui(index iIndex);
   virtual void set_timer(sp(::user::interaction) pui, uint_ptr nIDEvent, UINT nEllapse);
   virtual void unset_timer(sp(::user::interaction) pui, uint_ptr nIDEvent);
   virtual void set_auto_delete(bool bAutoDelete = true);
   virtual void set_run(bool bRun = true);
   virtual event & get_finish_event();
   virtual bool get_run();
   virtual thread * get_app_thread();
   virtual sp(::user::interaction) get_active_ui();
   virtual sp(::user::interaction) set_active_ui(sp(::user::interaction) pui);
   virtual void step_timer();
   virtual bool on_run_step();


   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
   virtual void Delete();
   // 'delete this' only if m_bAutoDelete == TRUE

   virtual void DispatchThreadMessageEx(signal_details * pobj);  // helper

   virtual int32_t main();





   virtual void wait();

#ifdef WINDOWS
   virtual HANDLE item() const;
#else
   virtual int_ptr item() const;
#endif



   virtual bool verb();



};

CLASS_DECL_BASE void thread_alloc_ready(bool bReady);









class CLASS_DECL_BASE thread_state
{
public:


   //heap_item_array                     m_heapitema;


};

CLASS_DECL_BASE thread * get_thread();
//CLASS_DECL_BASE thread_state * get_thread_state();


typedef thread * (*PFN_get_thread)();
typedef thread_state * (*PFN_get_thread_state)();

extern CLASS_DECL_BASE PFN_get_thread g_pfn_get_thread;
extern CLASS_DECL_BASE PFN_get_thread_state g_pfn_get_thread_state;

CLASS_DECL_BASE mutex & user_mutex();




