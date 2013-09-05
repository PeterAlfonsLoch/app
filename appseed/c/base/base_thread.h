#pragma once


#ifdef WINDOWSEX

typedef HANDLE HTHREAD;

#else

typedef hthread * HTHREAD;

#endif


class CLASS_DECL_c base_thread :
   virtual public object
{
public:


   thread *          m_pthread;


   base_thread();
   virtual ~base_thread();


   virtual HTHREAD get_os_handle() const;
   virtual int get_x_window_count() const;
   virtual void step_timer();
   virtual bool get_run();

   virtual bool verb();


   // called when occurs an standard_exception exception in run
   // return true to call run again
   virtual bool on_run_exception(::exception::exception & e);


};


namespace ca2
{

   class CLASS_DECL_c thread_state
   {
   public:


      //heap_item_array                     m_heapitema;


   };

   CLASS_DECL_c base_thread * get_thread();
   CLASS_DECL_c thread_state * get_thread_state();


   typedef base_thread * (* PFN_get_thread)();
   typedef thread_state * (* PFN_get_thread_state)();

   extern CLASS_DECL_c PFN_get_thread g_pfn_get_thread;
   extern CLASS_DECL_c PFN_get_thread_state g_pfn_get_thread_state;


} // namespace ca2



