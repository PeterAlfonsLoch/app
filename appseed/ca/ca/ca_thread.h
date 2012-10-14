#pragma once




/*namespace win
{
   class CLASS_DECL_ca message
   {
   public:
      ::user::interaction *  m_pguie;
      UINT              m_uiMessage;
      WPARAM            m_wparam;
      LPARAM            m_lparam;
      LRESULT send();
      static UINT ThreadProcSendMessage(LPVOID lp);
      static void post(::user::interaction * puie, UINT uiMessage, WPARAM wparam, LPARAM lparam, int nPriority = 0);
   };

} // namespace win*/

// incorporation of sector8J src/lib/pal/windows/thread_windows.hpp on 07/09/2011
/**
* \file		src/lib/pal/windows/thread_windows.hpp
* \brief	Platform independent threads and synchronization objects (windows version)
* \author	Thomas Nass
*/
// incorporation of sector8J src/lib/pal/windows/thread_linux.hpp on 23/09/2011
/**
* \file		src/lib/pal/linux/thread_linux.hpp
* \brief	Platform independent threads and synchronization objects (linux version)
* \author	Thomas Nass
*/

//#ifndef GEN_PAL_THREAD_WINDOWS_HPP
//#define GEN_PAL_THREAD_WINDOWS_HPP

// xxx #include "../waitable.hpp"

//#include <process.h>

//#include <stdexcept>
//#include <limits>


class event;


namespace radix
{


   class thread;


} // namespace radix


namespace ca
{

#ifdef WINDOWS

	///  \brief		global function to wait on a waitable item for a specified time
	///  \param		waitableItem item to wait for (can be event, socket, file, semaphore, ...)
	///  \param		duration time period to wait for item (default: infinite)
	///  \return	result of waiting action as defined in wait_result
	inline wait_result wait(event_base & waitableItem, const duration & duration = duration::infinite())
	{ return waitableItem.wait( duration ); }

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
	wait_result wait (event_base & waitableItem, const duration & duration=duration::infinite());

	///  \brief		global function to wait on a waitable item for a specified time
	///  \param		waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
	///  \param		duration time period to wait for item (default: infinite)
	///  \return	result of waiting action as defined in wait_result
	wait_result wait (size_t numberOfItems, event_base * waitableItems[], const duration& duration=duration::infinite(), bool waitForAll = false);

#endif

   class CLASS_DECL_ca heap_item
   {
   public:


      byte *      m_pbStart;
      byte *      m_pbEnd;
#ifdef MERDE_WINDOWS
      DWORD64     m_dwTickCount;
#else
      DWORD       m_dwTickCount;
#endif


      inline heap_item()
      {
         m_pbStart = NULL;
         m_pbEnd = NULL;
      }


#ifdef MERDE_WINDOWS
      inline heap_item(void * p, ::primitive::memory_size iSize, DWORD64 dwTick)
#else
      inline heap_item(void * p, ::primitive::memory_size iSize, DWORD dwTick)
#endif
      {
         m_pbStart = (byte *) p;
         m_pbEnd = ((byte *) p) + max(iSize - 1, 0);
         m_dwTickCount = dwTick;
      }


      inline char compare(void * p)
      {
         if(((byte *)p) <= m_pbStart)
            return 1;
         else if(((byte *)p) >= m_pbEnd)
            return -1;
         else
            return 0;
      }

      inline bool contains(void * p)
      {
         if(((byte *)p) <= m_pbStart)
            return false;
         else if(((byte *)p) >= m_pbEnd)
            return false;
         else
            return true;
      }

   };

   class CLASS_DECL_ca heap_item_array :
      public simple_array < heap_item, heap_item >
   {
   public:

#ifdef MERDE_WINDOWS
      DWORD64 m_dwLastCleanup;
#else
      DWORD m_dwLastCleanup;
#endif

      inline void add_item(void * p, ::primitive::memory_size iSize)
      {
#ifdef MERDE_WINDOWS
         add(heap_item(p, iSize, GetTickCount64()));
         if(GetTickCount64() > m_dwLastCleanup + 10000)
#else
         add(heap_item(p, iSize, get_tick_count()));
         if(get_tick_count() > m_dwLastCleanup + 10000)
#endif
         {
            cleanup();
         }
      }

      inline void cleanup()
      {
#ifdef MERDE_WINDOWS
         DWORD64 dwLimit = GetTickCount64() - 1000;
#else
         DWORD64 dwLimit = get_tick_count() - 1000;
#endif
         for(int i = 0; i < this->get_count();)
         {
            if(dwLimit > m_pData[i].m_dwTickCount)
            {
               remove_at(i);
            }
            else
            {
               i++;
            }
         }
#ifdef MERDE_WINDOWS
         m_dwLastCleanup = GetTickCount64();
#else
         m_dwLastCleanup = get_tick_count();
#endif
      }

      inline bool find(void * p, bool bRemove)  // lAyana e Mi tsuo tsumanumA
      {
         UNREFERENCED_PARAMETER(bRemove);

         for(int mi = 0; mi < this->get_count(); mi++)
         {
            if(m_pData[mi].contains(p))
            {
               remove_at(mi);
               return true;
            }
         }
         return false;
      }

      /*inline void set_heap_alloc(::ca::ca * pca)
      {
         if(find(pca, true))
         {
            pca->m_ulFlags |= ::ca::ca::flag_heap_alloc;
         }
      }*/

   };


   class CLASS_DECL_ca thread_state
   {
   public:


      //heap_item_array                     m_heapitema;


   };

   class CLASS_DECL_ca thread :
      virtual public command_target,
      virtual public ::exception::translator,
      virtual public pha(::user::interaction),
      virtual public ::ca::live_object,
      virtual public event_base
   {
   public:
		/// thread ID, used to ensure that the thread that calls one of the
		/// wait methods is really the thread represented by the Thread class
	//	DWORD threadId_;


//	private:


      bool                                m_bRun;
      user::LPWndArray *                  m_puiptra;
      ::user::interaction::timer_array *  m_ptimera;
      comparable_array < ::ca::ca * >     m_captraDeletePool;
      bool                                m_bAutoDelete;       // enables 'delete this' after thread termination
      dword_ptr                           m_dwAlive;
      bool                                m_bReady;
      int                                 m_iReturnCode;
      ::ca::application *                 m_pappDelete;
      ph(::user::interaction)             m_puiMain;           // main window (usually same System.GetMainWnd())
      ph(::user::interaction)             m_puiActive;         // active main window (may not be GetMainWnd())
      bool *                              m_pbReady;
      gen::property_set                   m_set;
      string                              m_strWorkUrl;


      thread();
      virtual ~thread();

		///  \brief		starts thread on first call
		virtual void start ();

      virtual void * get_os_data() const;
      virtual int_ptr get_os_int() const;

      virtual void set_p(::radix::thread * p);


      virtual void set_os_data(void * pvoidOsData);
      virtual void set_os_int(int_ptr iData);


      friend bool __internal_pre_translate_message(MSG* pMsg);

      virtual void construct();
      virtual void construct(__THREADPROC pfnThreadProc, LPVOID pParam);

      virtual int main();

      virtual void CommonConstruct();

      virtual bool Begin(::ca::e_thread_priority epriority = thread_priority_normal, UINT nStackSize = 0, DWORD dwCreateFlags = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      virtual bool create_thread(DWORD dwCreateFlags = 0, UINT nStackSize = 0, LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL);

      virtual ::ca::e_thread_priority get_thread_priority();
      virtual bool set_thread_priority(::ca::e_thread_priority epriority);

      virtual DWORD SuspendThread();
      virtual DWORD ResumeThread();
      virtual bool post_thread_message(UINT message, WPARAM wParam, LPARAM lParam);
      virtual bool post_message(::user::interaction * pguie, UINT message, WPARAM wParam, LPARAM lParam);

      virtual bool PreInitInstance();

      // called when occurs an standard_exception exception in run
      // return true to call run again
      virtual bool on_run_exception(::ca::exception & e);

   // Overridables
      // thread initialization
      virtual bool initialize_instance();

      virtual bool finalize();

      virtual int exit();

      virtual ::gen::message::e_prototype GetMessagePrototype(UINT uiMessage, UINT uiCode);

      // running and idle processing
      virtual int run();
      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual bool pump_message();     // low level message pump
      virtual bool on_idle(LONG lCount); // return TRUE if more idle processing
      virtual bool is_idle_message(gen::signal_object * pobj);  // checks for special messages

      // thread termination
      virtual int exit_instance(); // default will 'delete this'

      // Advanced: exception handling
      virtual void ProcessWndProcException(base_exception * e, gen::signal_object * pobj);

      // Advanced: handling messages sent to message filter hook
      virtual void ProcessMessageFilter(int code, gen::signal_object * pobj);

      // Advanced: virtual access to GetMainWnd()
      virtual ::user::interaction * GetMainWnd();
      virtual ::user::interaction * SetMainWnd(::user::interaction * pui);

      using pha(::user::interaction)::add;
      virtual void add(::user::interaction * pui);

      using pha(::user::interaction)::remove;
      virtual void remove(::user::interaction * pui);

      virtual ::count get_ui_count();
      virtual ::user::interaction * get_ui(index iIndex);
      virtual void set_timer(::user::interaction * pui, uint_ptr nIDEvent, UINT nEllapse);
      virtual void unset_timer(::user::interaction * pui, uint_ptr nIDEvent);
      virtual void set_auto_delete(bool bAutoDelete = true);
      virtual void set_run(bool bRun = true);
      virtual event & get_finish_event();
      virtual bool get_run();
      virtual ::ca::thread * get_app_thread();
      virtual ::user::interaction * get_active_ui();
      virtual ::user::interaction * set_active_ui(::user::interaction * pui);
      virtual void step_timer();

      virtual void on_delete(::ca::ca * p);


      virtual bool verb();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual void Delete();
         // 'delete this' only if m_bAutoDelete == TRUE

      virtual void DispatchThreadMessageEx(gen::signal_object * pobj);  // helper

      virtual void on_keep_alive();
      virtual bool is_alive();


      virtual bool has_message();




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
		// int wait (unsigned TimeoutMs, unsigned NumberOfEvents, ...);

		//void suspend ()
		//{ ::SuspendThread(item()); }
		//
		//void resume ()
		//{ ::ResumeThread(item()); }

		///  \brief		waits for signaling the thread forever
		virtual void wait();

		///  \brief		waits for signaling the thread for a specified time
		///  \param		duration time period to wait for thread
		///  \return	result of waiting action as defined in wait_result
		virtual wait_result wait(const duration & duration);

		///  \brief		sets thread priority
		///  \param		new priority
		void set_priority(int priority);

		///  \brief		gets thread priority
		///  \param		priority
		int priority();

		///  \brief		destructor
//		virtual ~Thread()
	//	{}
//
	//	Thread (const Thread &);				// no copy constructor
		//Thread & operator= (const Thread &);	// no assignment operator

		/*static unsigned __stdcall startExecution_ (thread * thisThread)
		{
			thisThread->threadId_ = ::GetCurrentThreadId();
			unsigned result = (*thisThread)();
			if (result == autodelete)
				delete thisThread;
			return result;
		}*/

		//virtual unsigned operator() () = 0;

      virtual bool is_auto_delete();
	//};


//#endif // #define GEN_PAL_THREAD_WINDOWS_HPP

//#pragma comment(exestr,"$Id: thread_windows.hpp,v 1.19 2011/02/21 14:09:43 cle Exp $")
//
// EoF
///////

   };

   typedef smart_pointer < thread > thread_sp;

   CLASS_DECL_ca thread * get_thread();
   CLASS_DECL_ca thread_state * get_thread_state();


   typedef thread * (* PFN_get_thread)();
   typedef thread_state * (* PFN_get_thread_state)();

   extern CLASS_DECL_ca PFN_get_thread g_pfn_get_thread;
   extern CLASS_DECL_ca PFN_get_thread_state g_pfn_get_thread_state;



} // namespace ca



